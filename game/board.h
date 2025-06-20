#ifndef WORDLEBOT_GAME_BOARD_H_
#define WORDLEBOT_GAME_BOARD_H_

#include <string>
#include <iostream>

#include "../utils/hint.h"

const int WIDTH = 5;
const int HEIGHT = 6;

class Board {
    public:
        Board() : answer_("error") {};
        Board(const std::string answer);

        void makeGuess(const std::string guess);

        Hint *getPreviousGuessHints();
        char *getGuess(int index) { return board_[index]; }
        int index() const { return index_; }
        char** board() const { return board_; }
        Hint **hints() const { return hints_; }
        friend std::ostream& operator<<(std::ostream& os, Board board);

    private:
        int index_;
        std::string answer_;
        char** board_;
        Hint **hints_;

        void check(const std::string guess);
}; // class Board

#endif // WORDLEBOT_GAME_BOARD_H_