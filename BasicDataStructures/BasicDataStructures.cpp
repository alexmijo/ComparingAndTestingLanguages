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

// TODO: Be more general by making these templates (I think) so the types they contain don't just
//  have to be ints.

// When there's an optional parameter, include it in the function's declaration but not in the
//  function's definition
void printIntsInArray(const int[], const int, const std::string& separator=" ");

void printIntsInLibraryArray(const std::array<int, 3>& array, const std::string& separator=" ") {
    for (const int element : array) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

void printIntsInVector(const std::vector<int>& vector, const std::string& separator=" ") {
    for (const int element : vector) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

void printIntsInOrderedSet(const std::set<int>& set, const std::string& separator=" ") {
    for (const int element : set) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

void printIntsInUnorderedSet(const std::unordered_set<int>& set, const std::string& separator=" ") {
    for (const int element : set) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

void printIntIntsInOrderedMap(const std::map<int, int>& map, const std::string& separator=", ") {
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

void printIntIntsInUnorderedMap(const std::unordered_map<int, int>& map,
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
    printIntsInArray(fixedLenListOfInts, KNOWN_LIST_LENGTH);
    // Alternative
    std::array<int, KNOWN_LENGTH> fixedLenListOfInts3;
    printIntsInLibraryArray(fixedLenListOfInts3);

    // Fixed length not known at compile time
    // I think stack overflow said this was a bad idea:
    int notKnownLength = 0;
    notKnownLength += 3;
    int *fixedLenListOfInts2 = new int[notKnownLength];
    printIntsInArray(fixedLenListOfInts2, notKnownLength);
    delete[] fixedLenListOfInts2;
    // If I don't need to reassign values, I can do something like this (I think size doesn't have
    //  to be known at compile time just cause the const vector can be initialized using an
    //  allocator, whatever that is)
    const std::vector<int> fixedLenListOfInts4{15, 16, 17}; // TODO: Figure out allocator
    // Expression must be a modifiable lvalue
    // fixedLenListOfInts4.at(0) = 21;
    printIntsInVector(fixedLenListOfInts4);
    // So bassically in an interview (and my code at least for now), I should do this sort of thing:
    std::vector<int> pseudoFixedLenListOfInts(notKnownLength);
    pseudoFixedLenListOfInts[0] = 5;
    // Doesn't do what I thought it did at first.
    // pseudoFixedLenListOfInts.assign(1, 6);
    pseudoFixedLenListOfInts.at(1) = 6;
    pseudoFixedLenListOfInts.back() = 7;
    printIntsInVector(pseudoFixedLenListOfInts);

    // Variable length
    std::vector<int> variableLenListOfInts(4);
    for (int i = 0; i < 4; i++) {
        variableLenListOfInts.at(i) = i * 2;
    }
    variableLenListOfInts.push_back(45);
    printIntsInVector(variableLenListOfInts);

    //----------------------------------------------------------------------------------------------
    // Sets
    // Sorted, usually implemented as red black tree (O(log n))
    std::set<int> orderedSetOfInts = {500, 45000, 600};
    printIntsInOrderedSet(orderedSetOfInts);
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
    printIntsInUnorderedSet(unorderedSetOfInts);
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
    printIntIntsInOrderedMap(orderedMapOfInts);
    std::cout << (orderedMapOfInts.find(-5) != orderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    orderedMapOfInts.erase(-5);
    std::cout << (orderedMapOfInts.find(-5) != orderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    printIntIntsInOrderedMap(orderedMapOfInts);

    // Unsorted, a HashMap (like with sets) (O(1))
    std::unordered_map<int, int> unorderedMapOfInts;
    unorderedMapOfInts[-5] = 25;
    unorderedMapOfInts[4] = 16;
    unorderedMapOfInts[3] = 9;
    printIntIntsInUnorderedMap(unorderedMapOfInts);
    std::cout << (unorderedMapOfInts.find(-5) != unorderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    unorderedMapOfInts.erase(-5);
    std::cout << (unorderedMapOfInts.find(-5) != unorderedMapOfInts.end() ? "true" : "false")
        << std::endl;
    printIntIntsInUnorderedMap(unorderedMapOfInts);
}

// <separator> optional
void printIntsInArray(const int array[], const int length, const std::string& separator) {
    for (int i = 0; i < length - 1; i++) {
        std::cout << array[i] << separator;
    }
    std::cout << array[length - 1] << std::endl;
}