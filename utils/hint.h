#ifndef WORDLE_UTILS_HINT_H_
#define WORDLE_UTILS_HINT_H_

typedef enum Hint {
    WHITE = 3,
    GRAY = 2,
    YELLOW = 1,
    GREEN = 0
} Hint;

int convertToInt(Hint hints[], int length);

Hint *convertFromInt(int num, int maxLength);

#endif // WORDLE_UTILS_HINT_H_