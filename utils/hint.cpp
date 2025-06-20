#include <math.h>

#include "hint.h"

 int convertToInt(Hint hints[], int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result += pow(3, length - i - 1) * hints[i];
    }
    return result;
 }

 Hint *convertFromInt(int num, int maxLength) {
    Hint *arr = new Hint[maxLength];
    for (int i = 1; i <= maxLength; ++i) {
        int index = maxLength - i;
        int bit = pow(3, index);
        if (num >= bit * 2) {
            arr[index] = GREEN;
        } else if (num >= bit) {
            arr[index] = YELLOW;
        } else {
            arr[index] = GRAY;
        }
    }
    return arr;
 }