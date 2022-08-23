#include <iostream>
#include <vector>
#include "CppUtilities.cpp"

using namespace std;

int main() {
    vector<vector<int>> bigVec(10, vector<int>(3, 3));
    for (const auto& vec : bigVec) {
        printVector(vec);
    }
}