
#include <string>
#include <cstdlib>
#include <ctime>


#include "wordle.h"
#include "board.h"
#include "../utils/hint.h"

const std::string VALID_ANSWERS = "game/assets/valid-wordle-solutions.txt";
const std::string VALID_GUESSES = "game/assets/valid-wordle-words.txt";

std::string randomWord(std::vector<std::string> list) {
    srand(time(0));
    int n = rand() % list.size();
    return list.at(n);
}

Wordle::Wordle() : loader_(VALID_GUESSES, VALID_ANSWERS), currentGameState_(ONGOING) {
    loader_.load();
    board_ = Board(randomWord(loader_.validAnswers()));
}

Wordle::Wordle(std::string answer) : board_(answer), loader_(VALID_GUESSES, VALID_ANSWERS), currentGameState_(ONGOING) {
    loader_.load();
}

bool Wordle::makeGuess(const std::string guess) {
    if (!loader_.containsGuess(guess)) return false;
    this->board_.makeGuess(guess);
    if (convertToInt(board_.getPreviousGuessHints(), WIDTH) == 0) {
        currentGameState_ = WIN;
    } else if (board_.index() >= HEIGHT) {
        currentGameState_ = LOSS;
    }
    return true;
} // Wordle::makeGuess(std::string guess)
