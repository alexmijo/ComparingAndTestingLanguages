#include <iostream>
#include <stdlib.h>
#include <vector>

int main() {
    std::vector<std::vector<long>> numMNInARowsNoOverlap(11, std::vector<long>(11));
    std::vector<std::vector<long>> numMNInARowsOverlapAllowed(11, std::vector<long>(11));

    for (long i = 0; i < 10000000000; i++) {
        std::vector<long> numNInARowsNoOverlap(11);
        std::vector<long> numNInARowsOverlapAllowed(11);
        int consecutive = 1;
        long j = i;
        int digit = j % 10;

        for (int i = 0; i < 9; i++) {
            j /= 10;
            int nextDigit = j % 10;
            if (nextDigit == digit) {
                consecutive++;
                for (int n = 1; n <= consecutive; n++) {
                    numNInARowsOverlapAllowed[n]++;
                    if (consecutive % n == 0) {
                        numNInARowsNoOverlap[n]++;
                    }
                }
            } else {
                digit = nextDigit;
                consecutive = 1;
            }
        }
        for (int m = 0; m < 11; m++) {
            for (int n = 0; n < 11; n++) {
                if (numNInARowsOverlapAllowed[n] >= m) {
                    numMNInARowsOverlapAllowed[m][n]++;
                }
                if (numNInARowsNoOverlap[n] >= m) {
                    numMNInARowsNoOverlap[m][n]++;
                }
            }
        }
        if (numNInARowsNoOverlap[3] > 1 && (((i + 1) % 31 == 0 && i % 15 == 4) || (i + 1) % 10000000 == 0)) {
            std::cout << (i + 1) << ": " << ((long double) numMNInARowsNoOverlap[1][3]) / ((i + 1) * 100)
                      << "  ---  " << i << "\n";
        }
    }
}