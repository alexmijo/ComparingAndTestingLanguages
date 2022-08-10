class SimpleClass {
private:

    int value;

public:

    SimpleClass(int value) : value(value) {}

    int getValue() const {
        return value;
    }

    void setValue(int value) {
        this->value = value;
    }
};