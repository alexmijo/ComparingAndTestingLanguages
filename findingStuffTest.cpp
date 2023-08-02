#include <iostream>
#include <unordered_map>
#include <chrono>

int main() {
    std::unordered_map<int, std::string> digitNames = {
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

    const auto it = digitNames.find(3);
    if (it != digitNames.end()) {
        std::cout << it->second << '\n';
    }
}