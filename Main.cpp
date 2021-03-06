#include "OtherCppCode/DeepClass.cpp"
#include <iostream>

void mutateSimpleObject(SimpleClass simpleObject, int newValue);
// Variable names not needed
void reassignSimpleObject(SimpleClass, int);
void mutateDeepObject(DeepClass, int, int, int); // Don't use
void betterMutateDeepObject(DeepClass&, int, int, int); // Need the &
void mutateBetterDeepObject(BetterDeepClass, int, int, int);

int main() {
    SimpleClass simpleObject(3);
    std::cout << "After initialization: " << simpleObject.getValue() << std::endl;

    mutateSimpleObject(simpleObject, 4);
    std::cout << "After mutateSimpleObject: " << simpleObject.getValue() << std::endl;

    reassignSimpleObject(simpleObject, 5);
    std::cout << "After reassignSimpleObject: " << simpleObject.getValue() << std::endl;

    SimpleClass newSimpleObject(6);
    simpleObject = newSimpleObject;
    std::cout << "After reassignment: " << simpleObject.getValue() << std::endl;
    
    // Conclusion: There is actually a copy being done when passing in a parameter.
    
    // Test whether that copy is shallow or deep, and how pointers affect things:
    std::cout << "Now, DeepClass:" << std::endl;
    DeepClass deepObject(1, 2, 3);
    std::cout << "Object value after initialization: " << deepObject.getObjectValue() << std::endl
              << "Pointer value after initialization: " << deepObject.getPointerValue() << std::endl
              << "Shallow value after initialization: " << deepObject.getShallowValue()
              << std::endl;

    /*
    mutateDeepObject(deepObject, 4, 5, 6); // Actually, pointer gets deleted here!
    // The copy in the function call went out of scope, calling its destructor!
    std::cout << "Object value after mutateDeepObject: " << deepObject.getObjectValue() << std::endl
              << "Pointer value after mutateDeepObject: " << deepObject.getPointerValue()
              << std::endl << "Shallow value after mutateDeepObject: "
              << deepObject.getShallowValue() << std::endl;

    // Bad cause it causes a double (edit: triple) delete for pointer
    DeepClass newDeepObject = deepObject;
    */

    // Need to pass deepObject by reference to avoid making a copy and therefore avoid the above
    //  issues. Really just shouldn't have a pointer in there that is deleted in it's destructor
    //  though. Sort of defeats the point of the test anyways.
    betterMutateDeepObject(deepObject, 4, 5, 6);
    std::cout << "Object value after betterMutateDeepObject: " << deepObject.getObjectValue()
              << std::endl << "Pointer value after betterMutateDeepObject: "
              << deepObject.getPointerValue() << std::endl
              << "Shallow value after betterMutateDeepObject: " << deepObject.getShallowValue()
              << std::endl;
    // Still can't do this cause it'd cause a double delete for pointer. Deep class is really not
    //  good.
    // DeepClass newDeepObject = deepObject;

    std::cout << "Now, BetterDeepClass:" << std::endl;
    SimpleClass pointedToSimpleObject(2); 
    BetterDeepClass betterDeepObject(1, &pointedToSimpleObject, 3);
    std::cout << "Object value after initialization: " << betterDeepObject.getObjectValue()
              << std::endl << "Pointer value after initialization: "
              << betterDeepObject.getPointerValue() << std::endl
              << "Shallow value after initialization: " << betterDeepObject.getShallowValue()
              << std::endl;

    mutateBetterDeepObject(betterDeepObject, 4, 5, 6);
    std::cout << "Object value after mutateBetterDeepObject: " << betterDeepObject.getObjectValue()
              << std::endl << "Pointer value after mutateBetterDeepObject: "
              << betterDeepObject.getPointerValue() << std::endl
              << "Shallow value after mutateBetterDeepObject: "
              << betterDeepObject.getShallowValue() << std::endl;

    // Conclusion: The copy is deep (as I understand the term), but not through pointers.

    BetterDeepClass newBetterDeepObject = betterDeepObject;
    newBetterDeepObject.setObjectValue(7);
    newBetterDeepObject.setPointerValue(8);
    newBetterDeepObject.setShallowValue(9);
    std::cout << "betterDeepObject.getObjectValue(): " << betterDeepObject.getObjectValue()
              << std::endl << "betterDeepObject.getPointerValue(): "
              << betterDeepObject.getPointerValue() << std::endl
              << "betterDeepObject.getShallowValue(): " << betterDeepObject.getShallowValue()
              << std::endl;
    std::cout << "newBetterDeepObject.getObjectValue(): " << newBetterDeepObject.getObjectValue()
              << std::endl << "newBetterDeepObject.getPointerValue(): "
              << newBetterDeepObject.getPointerValue() << std::endl
              << "newBetterDeepObject.getShallowValue(): " << newBetterDeepObject.getShallowValue()
              << std::endl;
    // The above all works as expected
}

void mutateSimpleObject(SimpleClass simpleObject, int newValue) {
    simpleObject.setValue(newValue);
}

void reassignSimpleObject(SimpleClass simpleObject, int newSimpleClassValue) {
    SimpleClass newSimpleObject(newSimpleClassValue);
    simpleObject = newSimpleObject;
}

// Very bad, don't use
void mutateDeepObject(DeepClass deepObject, int newObjectValue, int newPointerValue,
                      int newShallowValue) {
    deepObject.setObjectValue(newObjectValue);
    deepObject.setPointerValue(newPointerValue);
    deepObject.setShallowValue(newShallowValue);
}

void betterMutateDeepObject(DeepClass& deepObject, int newObjectValue, int newPointerValue,
                            int newShallowValue) {
    deepObject.setObjectValue(newObjectValue);
    deepObject.setPointerValue(newPointerValue);
    deepObject.setShallowValue(newShallowValue);
}

void mutateBetterDeepObject(BetterDeepClass betterDeepObject, int newObjectValue,
                            int newPointerValue, int newShallowValue) {
    betterDeepObject.setObjectValue(newObjectValue);
    betterDeepObject.setPointerValue(newPointerValue);
    betterDeepObject.setShallowValue(newShallowValue);
}