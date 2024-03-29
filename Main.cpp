#include "OtherCppCode/DeepClass.cpp"
#include "OtherCppCode/CppUtilities.cpp"
#include <iostream>
#include <vector>
#include <memory>

void mutateSimpleObject(SimpleClass simpleObject, int newValue);
// Variable names not needed
void reassignSimpleObject(SimpleClass, int);
void mutateDeepObject(DeepClass, int, int, int); // Don't use
void betterMutateDeepObject(DeepClass&, int, int, int); // Need the &
void mutateBetterDeepObject(BetterDeepClass, int, int, int);

void modifyValueUniquePointer(const std::unique_ptr<SimpleClass>& uniquePointer, int newValue) {
    uniquePointer->setValue(newValue);
}

template <>
void printVector(const std::vector<SimpleClass>& vector, const std::string& separator) {
    for (const SimpleClass element : vector) {
        // Trailing separator printed
        std::cout << element.getValue() << separator;
    }
    std::cout << std::endl;
}

// This function is useless lol
void modifyValueUniquePointerNotReference(std::unique_ptr<SimpleClass> uniquePointer,
                                          int newValue) {
    uniquePointer->setValue(newValue);
}

SimpleClass testTemporaryReturns(int value) {
    return SimpleClass(value);
}

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

    // Bad cause it causes a double (edit: triple) delete for pointer Edit again: Why did I say 
    //  triple?
    DeepClass newDeepObject = deepObject;
    */

    // Need to pass deepObject by reference to avoid making a copy and therefore avoid the above
    //  issues. Really just shouldn't have a pointer in there that is deleted in it's destructor
    //  though. Sort of defeats the point of the test anyways.
    // Edit: Actually couldn't I still do RAII the C way fairly safely just by removing its default
    //  copy constructor?
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

    std::vector<SimpleClass*> vec;
    for (int value = 1; value <= 5; value++) {
        SimpleClass simpleElement(value);
        vec.push_back(&simpleElement);
    }
    for (auto simplePointer : vec) {
        std::cout << simplePointer->getValue() << std::endl;
    }
    // The above didn't work.

    std::cout << std::endl;
    std::vector<SimpleClass*> vec1;
    for (int value = 1; value <= 5; value++) {
        SimpleClass *simpleElement = new SimpleClass(value);
        vec1.push_back(simpleElement);
    }
    for (auto simplePointer : vec1) {
        std::cout << simplePointer->getValue() << std::endl;
    }
    // That works, but I have to remember to delete.
    for (auto simplePointer : vec1) {
        delete simplePointer;
    }

    // Basically, I want to use shared_ptr, I think
    std::cout << std::endl;
    std::vector<std::shared_ptr<SimpleClass>> vec2;
    for (int value = 1; value <= 5; value++) {
        SimpleClass *simpleElement = new SimpleClass(value);
        std::shared_ptr<SimpleClass> simpleEl(simpleElement);
        // Also works:
        // std::shared_ptr<SimpleClass> simpleElement = std::make_shared<SimpleClass>(value);
        vec2.push_back(simpleEl);
    }
    for (auto simplePointer : vec2) {
        std::cout << simplePointer->getValue() << std::endl;
    }

    std::unique_ptr<SimpleClass> unPointer = std::make_unique<SimpleClass>(7);
    modifyValueUniquePointer(unPointer, 8);
    std::cout << unPointer->getValue() << std::endl;

    // Doesn't work, unique_ptrs can't be copied
    // modifyValueUniquePointerNotReference(unPointer, 9);
    // But watch out! This compiles but gets segmentation error since unPointer gets moved to inside
    //  the function and then deleted after going out of scope when the function returns.
    // modifyValueUniquePointerNotReference(std::move(unPointer), 9);

    // Gotta remember I can use all three of these, and all three do constructor calls. a and b have
    //  constructor calls that return temporary (unnamed) objects.
    SimpleClass a = testTemporaryReturns(1);
    SimpleClass b = SimpleClass(2);
    SimpleClass c(3);

    std::cout << a.getValue() << " " << b.getValue() << " " << c.getValue() << std::endl;

    // Don't have to worry about the below since an alias can't be re-aliased, therefore it can only
    //  exist in the same scope as the thing it's aliasing.

    // std::unique_ptr<SimpleClass>& unPointyAlias; <<<<< Problem here
    // {
    //     std::unique_ptr<SimpleClass> unPointy = std::make_unique<SimpleClass>(10);
    //     unPointyAlias = unPointy;
    // }
    // std::cout << unPointyAlias->getValue() << std::endl;

    // This is fine, when the alias goes out of scope it must know it's just an alias I guess. I
    //  suppose when thinking more generally about aliases that's the only thing that'd actually
    //  make sense anyways.
    std::unique_ptr<SimpleClass> unPointy = std::make_unique<SimpleClass>(10);
    {
        std::unique_ptr<SimpleClass>& unPointyAlias = unPointy;
    }
    std::cout << unPointy->getValue() << std::endl;

    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> v2 = v1;
    v2[3] = -100;
    printVector(v1);
    printVector(v2);
    std::vector<int> v3 = std::move(v2);
    printVector(v1);
    printVector(v2);
    printVector(v3);

    std::cout << std::endl;
    std::vector<SimpleClass> v4;
    v4.emplace_back(1);
    v4.emplace_back(2);
    v4.emplace_back(3);
    std::vector<SimpleClass> v5 = v4;
    v5[1].setValue(-33);
    printVector(v4);
    printVector(v5);
    std::vector<SimpleClass> v6 = std::move(v5);
    printVector(v4);
    printVector(v5);
    printVector(v6);

    int x = 2;
    int z = 3;
    auto y = (x + 0.5) / z;
    std::cout << x + 0.5 << std::endl;
    std::cout << y << std::endl;
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