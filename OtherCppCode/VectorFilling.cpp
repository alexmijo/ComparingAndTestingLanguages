#include <iostream>
#include <vector>
#include "CppUtilities.cpp"

using namespace std;

int main() {
    vector<vector<int>> bigVec(2, vector<int>(3, 3));
    for (const auto& vec : bigVec) {
        printVector(vec);
    }
    vector<int> testy{2, 0};
    vector<int> testy2(2, 0);
    vector<int> testy3({2, 0});
    // Can't do, must've been explicitely prohibited in vector's implementation somehow, I think.
    // vector<int> testy4(1, 2, 3, 5, 5);
    printVector(testy);
    printVector(testy2);
    printVector(testy3);
}