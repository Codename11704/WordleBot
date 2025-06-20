
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "dataloader.h"


void loadVector(std::string filename, std::vector<std::string> *vector) {
    std::string line;
    std::ifstream file(filename);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            vector->push_back(line);
        }
    }
}

void DataLoader::load() {
    loadVector(guessFilename_, &validGuesses_);
    loadVector(answerFilename_, &validAnswers_);
}

bool DataLoader::containsGuess(std::string guess) {
    for (std::string string : validGuesses_) {
        if (string.compare(guess) == 0) return true; 
    }
    return false;
}
