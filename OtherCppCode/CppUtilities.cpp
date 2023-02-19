#include <array>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
std::string vectorToString(const std::vector<T> &vector, const std::string &separator = " ") {
    if (vector.empty()) {
        return "";
    }
    std::stringstream ss;
    ss << vector[0];
    for (int i = 1; i < vector.size(); i++) {
        ss << separator << vector[i];
    }
    return ss.str();
}

// TODO: Templatized vs non-templatized (this one) useEndl
template <typename T>
void printVector(const std::vector<T> &vector, const std::string &separator = " ",
                 const bool useEndl = false) {
    std::cout << vectorToString(vector, separator);
    if (useEndl) {
        std::cout << std::endl;
    } else {
        std::cout << "\n";
    }
}

template <typename T1, typename T2>
void printPair(const std::pair<T1, T2> &p, bool printNewline = false) {
    std::cout << p.first << ", " << p.second;
    if (printNewline) {
        std::cout << "\n";
    }
}

template <>
void printVector(const std::vector<std::pair<int, int>> &vector, const std::string &separator,
                 const bool useEndl) {
    for (const std::pair<int, int> &element : vector) {
        printPair(element);
        // Trailing separator printed
        std::cout << separator;
    }
    if (useEndl) {
        std::cout << std::endl;
    } else {
        std::cout << "\n";
    }
}

template <typename T>
void printArray(const T array[], const int length, const std::string &separator = " ") {
    for (int i = 0; i < length - 1; i++) {
        std::cout << array[i] << separator;
    }
    std::cout << array[length - 1] << std::endl;
}

template <typename T, int size>
void printLibraryArray(const std::array<T, size> &array, const std::string &separator = " ") {
    for (const T &element : array) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}