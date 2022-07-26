#include <iostream>
//--------------------------------------------------------------------------------------------------
#include <string>
//--------------------------------------------------------------------------------------------------
#include <array>
//
#include <vector>
//--------------------------------------------------------------------------------------------------
#include <set>
//
#include <unordered_set>
//--------------------------------------------------------------------------------------------------
#include <map>
//
#include <unordered_map>


const int KNOWN_LENGTH = 3;

// When there's an optional parameter, include it in the function's declaration but not in the
//  function's definition
template <typename T>
void printArray(const T[], const int, const std::string& separator=" ");

template <typename T, int size>
void printLibraryArray(const std::array<T, size>& array, const std::string& separator=" ") {
    for (const T element : array) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

template <typename T>
void printVector(const std::vector<T>& vector, const std::string& separator=" ") {
    for (const T element : vector) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

template <typename T>
void printOrderedSet(const std::set<T>& set, const std::string& separator=" ") {
    for (const T element : set) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

template <typename T>
void printUnorderedSet(const std::unordered_set<T>& set, const std::string& separator=" ") {
    for (const T element : set) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

template <typename keyT, typename valueT>
void printOrderedMap(const std::map<keyT, valueT>& map, const std::string& separator=", ") {
    for (auto it = map.begin(); it != map.end(); it++) {
        std::cout << it->first << ": " << it->second;
        // Trailing separator not printed
        if (it != --map.end()) {
            std::cout << separator;
        } else {
            std::cout << std::endl;
        }
    }
}

template <typename keyT, typename valueT>
void printUnorderedMap(const std::unordered_map<keyT, valueT>& map,
                       const std::string& separator=", ") {
    int numPrintedSoFar = 0;
    for (auto it = map.begin(); it != map.end(); it++) {
        std::cout << it->first << ": " << it->second;
        // Trailing separator not printed
        if (numPrintedSoFar != map.size() - 1) {
            std::cout << separator;
        } else {
            std::cout << std::endl;
        }
        numPrintedSoFar++;
    }
}

int main() {
    //----------------------------------------------------------------------------------------------
    // Strings
    std::string stringThing = "Hi Mom";
    std::cout << stringThing.at(3) << std::endl;

    //----------------------------------------------------------------------------------------------
    // Lists
    // Fixed length known at compile time
    const int KNOWN_LIST_LENGTH = 10;
    int fixedLenListOfInts[KNOWN_LIST_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, 99, 111};
    printArray(fixedLenListOfInts, KNOWN_LIST_LENGTH);
    // Alternative
    std::array<int, KNOWN_LENGTH> fixedLenListOfInts3;
    printLibraryArray<int, KNOWN_LENGTH>(fixedLenListOfInts3);

    // Fixed length not known at compile time
    // I think stack overflow said this was a bad idea:
    int notKnownLength = 0;
    notKnownLength += 3;
    int *fixedLenListOfInts2 = new int[notKnownLength];
    printArray(fixedLenListOfInts2, notKnownLength);
    delete[] fixedLenListOfInts2;
    // If I don't need to reassign values, I can do something like this (I think size doesn't have
    //  to be known at compile time just cause the const vector can be initialized using an
    //  allocator, whatever that is)
    const std::vector<int> fixedLenListOfInts4{15, 16, 17}; // TODO: Figure out allocator
    // Expression must be a modifiable lvalue
    // fixedLenListOfInts4.at(0) = 21;
    printVector(fixedLenListOfInts4);
    // So bassically in an interview (and my code at least for now), I should do this sort of thing:
    std::vector<int> pseudoFixedLenListOfInts(notKnownLength);
    pseudoFixedLenListOfInts[0] = 5;
    // Doesn't do what I thought it did at first.
    // pseudoFixedLenListOfInts.assign(1, 6);
    pseudoFixedLenListOfInts.at(1) = 6;
    pseudoFixedLenListOfInts.back() = 7;
    printVector(pseudoFixedLenListOfInts);

    // Variable length
    std::vector<int> variableLenListOfInts(4);
    for (int i = 0; i < 4; i++) {
        variableLenListOfInts.at(i) = i * 2;
    }
    variableLenListOfInts.push_back(45);
    printVector(variableLenListOfInts);

    //----------------------------------------------------------------------------------------------
    // Sets
    // Sorted, usually implemented as red black tree (O(log n))
    std::set<int> orderedSetOfInts = {500, 45000, 600};
    printOrderedSet(orderedSetOfInts);
    std::cout << (orderedSetOfInts.find(500) != orderedSetOfInts.end() ? "true" : "false")
        << std::endl;
    std::cout << (orderedSetOfInts.find(550) != orderedSetOfInts.end() ? "true" : "false")
        << std::endl;
    orderedSetOfInts.emplace(550);
    // orderedSetOfInts.insert(550); also works, see cplusplus.com, difference is copy vs move vs
    //  construction vs other stuff
    std::cout << (orderedSetOfInts.find(550) != orderedSetOfInts.end() ? "true" : "false")
        << std::endl;
    orderedSetOfInts.erase(550);
    std::cout << (orderedSetOfInts.find(550) != orderedSetOfInts.end() ? "true" : "false")
        << std::endl;

    // Unsorted, a HashSet (O(1))
    std::unordered_set<int> unorderedSetOfInts = {499, 44999, 599};
    printUnorderedSet(unorderedSetOfInts);
    std::cout << (unorderedSetOfInts.find(499) != unorderedSetOfInts.end() ? "true" : "false")
        << std::endl;
    std::cout << (unorderedSetOfInts.find(550) != unorderedSetOfInts.end() ? "true" : "false")
        << std::endl;
    unorderedSetOfInts.emplace(550);
    // unorderedSetOfInts.insert(550); also works, see cplusplus.com, difference is copy vs move vs
    //  construction vs other stuff
    std::cout << (unorderedSetOfInts.find(550) != unorderedSetOfInts.end() ? "true" : "false")
        << std::endl;
    unorderedSetOfInts.erase(550);
    std::cout << (unorderedSetOfInts.find(550) != unorderedSetOfInts.end() ? "true" : "false")
        << std::endl;

    //----------------------------------------------------------------------------------------------
    // Maps
    // Sorted, usually implemented as red black tree (like with sets) (O(log n))
    std::map<int, int> orderedMapOfInts;
    orderedMapOfInts[4] = 16;
    orderedMapOfInts[-5] = 25;
    orderedMapOfInts[3] = 9;
    printOrderedMap(orderedMapOfInts);
    std::cout << (orderedMapOfInts.find(-5) != orderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    orderedMapOfInts.erase(-5);
    std::cout << (orderedMapOfInts.find(-5) != orderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    printOrderedMap(orderedMapOfInts);

    // Unsorted, a HashMap (like with sets) (O(1))
    std::unordered_map<int, int> unorderedMapOfInts;
    unorderedMapOfInts[-5] = 25;
    unorderedMapOfInts[4] = 16;
    unorderedMapOfInts[3] = 9;
    printUnorderedMap(unorderedMapOfInts);
    std::cout << (unorderedMapOfInts.find(-5) != unorderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    unorderedMapOfInts.erase(-5);
    std::cout << (unorderedMapOfInts.find(-5) != unorderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    printUnorderedMap(unorderedMapOfInts);
}

// <separator> optional
template <typename T>
void printArray(const T array[], const int length, const std::string& separator) {
    for (int i = 0; i < length - 1; i++) {
        std::cout << array[i] << separator;
    }
    std::cout << array[length - 1] << std::endl;
}