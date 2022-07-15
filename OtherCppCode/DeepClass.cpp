#include "SimpleClass.cpp"

class DeepClass {
private:

    SimpleClass simpleObject;
    SimpleClass *simplePointer;
    int shallowValue;

public:

    DeepClass(int objectValue, int pointerValue, int shallowValue) : simpleObject(objectValue),
        shallowValue(shallowValue) {
        simplePointer = new SimpleClass(pointerValue);
    }

    ~DeepClass() {
        delete simplePointer;
    }

    int getObjectValue() {
        return simpleObject.getValue();
    }

    void setObjectValue(int value) {
        simpleObject.setValue(value);
    }

    int getPointerValue() {
        return simplePointer->getValue();
    }

    void setPointerValue(int value) {
        simplePointer->setValue(value);
    }

    int getShallowValue() {
        return shallowValue;
    }

    void setShallowValue(int value) {
        shallowValue = value;
    }
};

class BetterDeepClass {
private:

    SimpleClass simpleObject;
    SimpleClass *simplePointer;
    int shallowValue;

public:

    BetterDeepClass(int objectValue, SimpleClass *simplePointer, int shallowValue) :
        simpleObject(objectValue), simplePointer(simplePointer), shallowValue(shallowValue) {}

    int getObjectValue() {
        return simpleObject.getValue();
    }

    void setObjectValue(int value) {
        simpleObject.setValue(value);
    }

    int getPointerValue() {
        return simplePointer->getValue();
    }

    void setPointerValue(int value) {
        simplePointer->setValue(value);
    }

    int getShallowValue() {
        return shallowValue;
    }

    void setShallowValue(int value) {
        shallowValue = value;
    }
};