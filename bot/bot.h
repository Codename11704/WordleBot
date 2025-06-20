#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <future>

#include "../templates/hashentry.h"

class Bot {
    public:
        Bot(std::string guessesFilename) : guessesFilename_(guessesFilename) {};

        std::vector<HashEntry<std::string, double>> predict(unsigned int size);
        void provideResults(std::string guess, int results);
        void prune();
        void load();
    private:
        std::string guessesFilename_;

        std::vector<std::string> possible_values_;

        std::string guess_;
        int results_;

        std::vector<HashEntry<std::string, double>> entropies_;

        int check(std::string answer, std::string guess);
        
        int calculateChange(std::string guess, int hints);
        double calculateProbability(std::string guess);
        void calculateEntropies();

};