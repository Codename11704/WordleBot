#include <iostream>
#include <string>

#include "game/wordle.h"


int main() {
    std::cout << "Wordle" << std::endl;
    Wordle game = Wordle();
    while (game.currentGameState() == ONGOING) {
        std::cout << "Insert Guess: ";
        std::string guess;
        std::cin >> guess;
        if(!game.makeGuess(guess)) {
            std::cout << "Invalid Guess" << std::endl;
            continue;
        }
        std::cout << game.board() << std::endl;
    }
    if (game.currentGameState() == WIN) {
        std::cout << "You Win" << std::endl;
    } else {
        std::cout << "You Lose" << std::endl;
    }
    return 0;
}


