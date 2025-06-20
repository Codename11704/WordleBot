#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

#include "templates/hashentry.h"
#include "utils/hint.h"
#include "bot/bot.h"
#include "game/board.h"

const std::string PATH = "game/assets/valid-wordle-words.txt";

const std::string ESCAPE = "n";

void printResults(std::vector<HashEntry<std::string, double>> results) {
    for (unsigned int i = 0; i < results.size(); ++i) {
        HashEntry<std::string, double> result = results[i];
        std::cout << i << ": " <<result.getKey() << ": " << result.getValue() << std::endl;
    }
}

int parseInput(std::string input) {
    Hint hints[WIDTH] = {WHITE, WHITE, WHITE, WHITE, WHITE};
    std::string::iterator it;
    int i = 0;
    for (char c : input) {
        switch (c) {
            case '0':
                hints[i] = GREEN;
                i++;
                break;
            case '1':
                hints[i] = YELLOW;
                i++;
                break;
            case '2':
                hints[i] = GRAY;
                i++;
                break;
        }
    }
    return convertToInt(hints, WIDTH);
}

std::string getString(std::string guessInt, std::vector<HashEntry<std::string, double>> results) {
    unsigned int num;
    std::stringstream ss(guessInt);
    if (!(ss >> num)) {
        return "";
    }
    if (num >= results.size()) {
        return "";
    }
    return results.at(num).getKey();
}

int main() {
    Bot bot = Bot(PATH);
    bot.load();
    std::cout << "Loaded" << std::endl;
    int flag = 1;
    while (flag) {
        auto start = std::chrono::steady_clock::now();
        std::vector<HashEntry<std::string, double>> results = bot.predict(10);
        auto end = std::chrono::steady_clock::now();
        auto duration = end - start;
        auto duration_sec = std::chrono::duration_cast<std::chrono::seconds>(duration);

        // Print elapsed time
        std::cout << "Elapsed time: " << duration_sec.count() << " seconds" << std::endl;
        printResults(results);

        // Have them pick from list
        std::cout << "Please input your choice: ";
        size_t index;
        std::cin >> index;

        std::string guess = results.at(index).getKey();

        std::cout << "0 = green, 1 = yellow, 2 = gray" << std::endl;
        std::cout << "Please insert hints: ";
        std::string hintString;
        std::cin >> hintString;
        std::cout << hintString << std::endl;
        if (hintString.compare(ESCAPE) == 0) {
            flag = 0;
            continue;
        }
        int hints = parseInput(hintString);
        std::cout << guess << " : " << hints << std::endl;
        bot.provideResults(guess, hints);
        bot.prune();
    }
    return 0;
}