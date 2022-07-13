#include "TestClass.cpp"
#include <iostream>

void mutateTestObject(TestClass testObject, int newValue);
// Variable names not needed, but I should probably have them anyways
void reassignTestObject(TestClass, int);

int main() {
    TestClass testObject(3);
    std::cout << "After initialization: " << testObject.getValue() << std::endl;

    mutateTestObject(testObject, 4);
    std::cout << "After mutateTestObject: " << testObject.getValue() << std::endl;

    reassignTestObject(testObject, 5);
    std::cout << "After reassignTestObject: " << testObject.getValue() << std::endl;

    TestClass newTestObject(6);
    testObject = newTestObject;
    std::cout << "After reassignment: " << testObject.getValue() << std::endl;
    
    // Conclusion: There is actually a copy being done when passing in a parameter.
    // TODO: Test whether that copy is shallow or deep.
}

void mutateTestObject(TestClass testObject, int newValue) {
    testObject.setValue(newValue);
}

void reassignTestObject(TestClass testObject, int newTestClassValue) {
    TestClass newTestObject(newTestClassValue);
    testObject = newTestObject;
}