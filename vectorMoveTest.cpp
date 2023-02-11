#include <stdlib.h>
#include <iostream>
#include <vector>
#include "OtherCppCode/CppUtilities.cpp"

int main() {
    for (int time = 0; time < 10; time++) {
        std::vector<std::string> vec1{"alex", "was", "here", "for", "real"};
        std::vector<std::string> vec2;
        printVector(vec1);
        
        for (int i = 1; i <= vec1.size(); i++) {
            vec2.emplace_back(std::move(vec1[vec1.size() - i]));
        }

        printVector(vec2);
    }
}