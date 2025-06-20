#include <iostream>
#include <fstream>
#include <math.h>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>

#include "bot.h"
#include "../game/board.h"
#include "../utils/hint.h"
//#include "../templates/hashentry.h"

const int MAX = 242;

double safe_log2(double n) {
    if (n == 0) return 0;
    return log2(n);
}

int Bot::check(std::string guess, std::string answer) {
    Hint hints[WIDTH];
    for (int i = 0; i < WIDTH; ++i) {
        hints[i] = WHITE;
    }
    for (int i = 0; i < WIDTH; ++i) {
        if (guess[i] == answer[i]) hints[i] = GREEN;
    } // for (int i = 0; i < WIDTH; ++i)
    for (int i = 0; i < WIDTH; ++i) {
        if (hints[i] != WHITE) continue;
        int total = 0;
        for (int j = 0; j < WIDTH; ++j) {
            if (guess[i] == answer[j]) ++total;
            if (i == j || (guess[i] == guess[j] && hints[j] <= YELLOW)) --total;
        } // for (int j = 0; j < WIDTH; ++j)
        if (total >= 0) {
            hints[i] = YELLOW;
        } else {
            hints[i] = GRAY;
        } // if (total >= 0)
    } // for (int i = 0; i < WIDTH; ++i)
    //std::cout << guess << " : " << answer << std::endl;
    //for (int i = 0; i < WIDTH; ++i) {
        //std::cout << hints[i] << " ";
    //}
    //std::cout << std::endl;
    return convertToInt(hints, WIDTH);
}

void Bot::prune() {
    std::cout << "Pruning " << guess_ << " with results " << results_ << std::endl;
    std::vector<std::string> pruned;
    for (unsigned int i = 0; i < possible_values_.size(); ++i) {
        //std::cout << possible_values_[i] << std::endl;
        int result = check(guess_, possible_values_[i]);
        if (result == results_) {
            //std::cout << "Answer " << possible_values_[i] << " valid\n";
            pruned.push_back(possible_values_[i]);
        }
    }
    std::cout << "Pruned " << possible_values_.size() - pruned.size() << " words" << std::endl;
    possible_values_ = pruned;
}

int Bot::calculateChange(std::string guess, int hints) {
    int numNew = 0;
    for (unsigned int i = 0; i < possible_values_.size(); ++i) {
        int result = check(guess, possible_values_[i]);
        //std::cout << result << std::endl;
        if (result == hints) {
            //std::cout << "match" << std::endl;
            ++numNew;
        }
    }
    return numNew;
}

double Bot::calculateProbability(std::string guess) {
    double total = 0;
    std::mutex lock;
    std::vector<std::future<int>> futures;
    for (int i = 0; i < MAX; ++i) {
        futures.push_back(std::async(std::launch::async, [guess, i, this]() {
            return calculateChange(guess, i);
        }));
    }
    for (std::future<int> &future : futures) {
        int change = future.get();
        if (change == 0) continue;
        total += (change * (safe_log2(possible_values_.size()) - safe_log2(change))) / possible_values_.size();
    }
    return total;
}

void Bot::calculateEntropies() {
    std::cout << "Calculating Entropies" << std::endl;
    entropies_.clear();
    unsigned int prog = 0;
    for (std::string guess : possible_values_) {
        double probability = calculateProbability(guess);
        //std::cout << probability << std::endl;
        double entropy = probability;
        size_t i = 0;
        while (i < entropies_.size() && entropy < entropies_.at(i).getValue()) {
            ++i;
        }
        entropies_.insert(entropies_.begin()+i, HashEntry<std::string, double>(guess, entropy));
        ++prog;
        std::cout << prog << " of " << possible_values_.size() << "\r";
    }
}

void Bot::load() {
    std::string line;
    std::ifstream file(guessesFilename_);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            possible_values_.push_back(line);
        }
    }
}

void Bot::provideResults(std::string guess, int results) {
    guess_ = guess;
    results_ = results;
}

std::vector<HashEntry<std::string, double>> Bot::predict(unsigned int size) {
    calculateEntropies();
    std::cout << "Calculation ended" << std::endl;
    std::vector<HashEntry<std::string, double>> list;
    for (unsigned int i = 0; i < size && i < entropies_.size(); ++i) {
        list.push_back(entropies_.at(i));
    }
    return list;
}

