#include <iostream>
#include <stdlib.h>
#include <vector>

int main() {
    long long times = 0;
    long long timesThreeInARow = 0;
    while (true) {
        bool hadThreeInARow = false;
        int consecutive = 1;
        int digit = rand() % 10;
        for (int i = 0; i < 9; i++) {
            int nextDigit = rand() % 10;
            if (nextDigit == digit) {
                consecutive++;
                if (consecutive == 3) {
                    hadThreeInARow = true;
                    break;
                }
            } else {
                digit = nextDigit;
                consecutive = 1;
            }
        }
        times++;
        if (hadThreeInARow) {
            timesThreeInARow++;
        }
        if (times % 1000000 == 0) {
            std::cout << times << ": " << ((long double)timesThreeInARow) / (times * 100)
                      << std::endl;
        }
    }
}