#include <iostream>
//--------------------------------------------------------------------------------------------------
#include <string>
//--------------------------------------------------------------------------------------------------
#include <array>
//
#include <vector>


const int KNOWN_LENGTH = 3;

// Keep in mind that if these arrays were big I would want to be passing them by reference, rather
//  than by value.

// When there's an optional parameter, include it in the function's declaration but not in the
//  function's definition
void printIntsInArray(const int[], const int, const std::string separator=" ");

void printIntsInLibraryArray(const std::array<int, 3> array, const std::string separator=" ") {
    for (int element : array) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
}

void printIntsInVector(const std::vector<int> vector, const std::string separator=" ") {
    for (int element : vector) {
        // Trailing separator printed
        std::cout << element << separator;
    }
    std::cout << std::endl;
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
    // TODO
}

// <separator> optional
void printIntsInArray(const int array[], const int length, const std::string separator) {
    for (int i = 0; i < length - 1; i++) {
        std::cout << array[i] << separator;
    }
    std::cout << array[length - 1] << std::endl;
}