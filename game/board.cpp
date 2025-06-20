#include <string>
#include <stdexcept>
#include <iostream>

#include "board.h"
#include "../utils/hint.h"

Board::Board(const std::string answer) : index_(0), answer_(answer) {
    index_ = 0;
    board_ = new char*[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        board_[i] = new char[WIDTH];
    } // for (int i = 0; i < HEIGHT; ++i)
    hints_ = new Hint*[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        hints_[i] = new Hint[WIDTH];
        for (int j = 0; j < WIDTH; ++j) {
            hints_[i][j] = WHITE;
        } // for (int j = 0; j < WIDTH; ++i)
    } // for (int i = 0; i < HEIGHT; ++i)
} // Board::board()

void Board::makeGuess(const std::string guess) {
    if (guess.length() != WIDTH) {
        throw new std::length_error("Incompatible guess size");
    } // if (guess.length() != WIDTH)
    for (int i = 0; i < WIDTH; ++i) {
        board_[index_][i] = guess[i];
    } // for (int i = 0; i < WIDTH; i++)
    check(guess);
    index_++;
} // Board::makeGuess(std::string guess)

void Board::check(const std::string guess) {
    Hint *hints = hints_[index_];
    for (int i = 0; i < WIDTH; ++i) {
        if (guess[i] == answer_[i]) hints[i] = GREEN;
    } // for (int i = 0; i < WIDTH; ++i)
    for (int i = 0; i < WIDTH; ++i) {
        if (hints[i] != WHITE) continue;
        int total = 0;
        for (int j = 0; j < WIDTH; ++j) {
            if (guess[i] == answer_[j]) ++total;
            if (i == j || (guess[i] == guess[j] && hints[j] <= YELLOW)) --total;
        } // for (int j = 0; j < WIDTH; ++j)
        if (total >= 0) {
            hints[i] = YELLOW;
        } else {
            hints[i] = GRAY;
        } // if (total >= 0)
    } // for (int i = 0; i < WIDTH; ++i)
}  // Board::check(std::string guess)

Hint* Board::getPreviousGuessHints() {
    return hints_[index_ - 1];
}

std::ostream& operator<<(std::ostream& os, Board board) {
    for (int i = 0; i < WIDTH; ++i) {
        os << board.hints()[board.index() - 1][i] << " ";
    }

    return os;
}