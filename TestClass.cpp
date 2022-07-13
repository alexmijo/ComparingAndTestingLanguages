class TestClass {
private:

    int value;

public:

    TestClass(int value) : value(value) {}

    int getValue() {
        return value;
    }

    void setValue(int value) {
        this->value = value;
    }
};