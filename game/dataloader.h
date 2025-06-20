#ifndef WORDLE_GAME_DATALOADER_H_
#define WORDLE_GAME_DATALOADER_H_

#include <string>
#include <vector>

class DataLoader {
    public:
        DataLoader(std::string guessFilename, std::string answerFilename) : guessFilename_(guessFilename), answerFilename_(answerFilename) {};

        void load();

        std::vector<std::string> validGuesses() const { return validGuesses_; }
        std::vector<std::string> validAnswers() const { return validAnswers_; }

        bool containsGuess(std::string string);


    private:
        std::string guessFilename_;
        std::string answerFilename_;

        std::vector<std::string> validGuesses_;
        std::vector<std::string> validAnswers_;
        
};

#endif // WORDLE_GAME_DATALOADER_H_