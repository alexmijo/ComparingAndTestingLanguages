#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "OtherCppCode/CppUtilities.cpp"

int64_t vectorMoveTest(const bool moveElems, const bool print = false) {
    const int64_t count = 10;
    const auto then = std::chrono::system_clock::now();
    for (int time = 0; time < count; time++) {
        std::vector<std::vector<std::string>> vec1(500, std::vector<std::string>(500, "alex"));
        std::vector<std::vector<std::string>> vec2;

        if (moveElems) {
            for (int i = 1; i <= vec1.size(); i++) {
                vec2.emplace_back(std::move(vec1[vec1.size() - i]));
            }
        } else {
            for (int i = 1; i <= vec1.size(); i++) {
                vec2.emplace_back(vec1[vec1.size() - i]);
            }
        }
    }
    const auto now = std::chrono::system_clock::now();
    const int64_t diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now - then).count();
    if (print) {
        std::cout << "time: " << diff << "ns" << std::endl;
        std::cout << "time / 1,000,000,000: " << (diff / 1000000000.) << "s" << std::endl;
        std::cout << count << std::endl;
    }
    return diff;
}

void runVectorMoveTests(const int numTimes = 1) {
    int64_t falseSum = 0;
    int64_t trueSum = 0;
    int i = 0;
    for (; i < numTimes / 2; i++) {
        falseSum += vectorMoveTest(false);
        trueSum += vectorMoveTest(true);
        trueSum += vectorMoveTest(true);
        falseSum += vectorMoveTest(false);
        std::cout << "num times: " << (i + 1)
                  << ", move avg: " << ((trueSum / ((i + 1) * 2)) / 1000000000.)
                  << ", copy avg: " << ((falseSum / ((i + 1) * 2)) / 1000000000.) << std::endl;
    }
    for (; i < numTimes; i++) {
        trueSum += vectorMoveTest(true);
        falseSum += vectorMoveTest(false);
        falseSum += vectorMoveTest(false);
        trueSum += vectorMoveTest(true);
        std::cout << "num times: " << (i + 1)
                  << ", move avg: " << ((trueSum / ((i + 1) * 2)) / 1000000000.)
                  << ", copy avg: " << ((falseSum / ((i + 1) * 2)) / 1000000000.) << std::endl;
    }
}

int64_t printVectorTest(const bool useFast, const bool print = false) {
    const auto then = std::chrono::system_clock::now();
    std::vector<std::string> vec1(1000000, "Alexander Paul Moreno");
    if (useFast) {
        //fastPrintVector(vec1);
    } else {
        printVector(vec1);
    }
    const auto now = std::chrono::system_clock::now();
    const int64_t diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now - then).count();
    if (print) {
        std::cout << (useFast ? "Fast" : "Not fast") << std::endl;
        std::cout << "time: " << diff << "ns" << std::endl;
        std::cout << "time / 1,000,000,000: " << (diff / 1000000000.) << "s" << std::endl;
    }
    return diff;
}

void runPrintVectorTests() {
    const int64_t notFast = printVectorTest(false);
    const int64_t fast = printVectorTest(true);
    bool useFast = false;
    for (int i = 0; i < 2; i++) {
        std::cout << (useFast ? "Fast" : "Not fast") << std::endl;
        std::cout << "time: " << (useFast ? fast : notFast) << "ns" << std::endl;
        std::cout << "time / 1,000,000,000: " << ((useFast ? fast : notFast) / 1000000000.) << "s"
                  << std::endl;
        useFast = true;
    }
}

int main() {
    const bool runMoveTests = false;
    if (runMoveTests) {
        runVectorMoveTests(30);
    } else {
        runPrintVectorTests();
    }
}