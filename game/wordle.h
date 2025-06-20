#ifndef WORDLEBOT_GAME_WORDLE_H_
#define WORDLEBOT_GAME_WORDLE_H_

#include <string>

#include "board.h"
#include "dataloader.h"
#include "../utils/hint.h"

enum GameState {
    ONGOING,
    WIN,
    LOSS
};

class Wordle {
public:
    Wordle();
    Wordle(std::string answer);

    bool makeGuess(const std::string guess);

    char **getGuesses() const { return board_.board(); }
    Hint **getHints() const { return board_.hints(); }
    Board board() const { return board_; }
    GameState currentGameState() { return currentGameState_; }

private:
    Board board_;
    std::string answer_;
    DataLoader loader_;
    GameState currentGameState_;

    std::string pickRandom();
    
};

#endif // WORDLEBOT_GAME_WORDLE_H_