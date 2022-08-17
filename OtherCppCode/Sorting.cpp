#include <vector>
#include <algorithm>
#include <array>
#include "CppUtilities.cpp"

// For custom hashing, look at HashTables.cpp in EoPI

template <typename T, int len>
bool myCompareArrays(std::array<T, len> array1, std::array<T, len> array2) {
    if (array1[0] == array2[0]) {
        return array1[1] < array2[1];
    }
    return array1[0] < array2[0];
}

template <>
void printVector(const std::vector<std::array<int, 4>>& vector, const std::string& separator) {
    std::cout << "{" << std::endl;
    for (const auto& element : vector) {
        // Trailing separator printed
        printLibraryArray<int, 4>(element);
    }
    std::cout << "}" << std::endl;
}

int main() {
    std::vector<int> list = {2, 4, 3, 1};
    printVector(list);
    std::sort(list.begin(), list.end());
    printVector(list);

    std::vector<std::array<int, 4>> list2;
    std::array<int, 4> elem1 = {4, 8, 11, 10};
    std::array<int, 4> elem2 = {10, 3, 2, 1};
    std::array<int, 4> elem3 = {4, 5, 7, 6};
    list2.emplace_back(std::move(elem1));
    list2.emplace_back(std::move(elem2));
    list2.emplace_back(std::move(elem3));
    // So the moves aren't actually doing anything
    // TODO: Test if it'd do something when the library arrays contain SimpleClasses
    printLibraryArray<int, 4>(elem1);
    printVector(list2);
    std::sort(list2.begin(), list2.end(), myCompareArrays<int, 4>);
    printVector(list2);
}