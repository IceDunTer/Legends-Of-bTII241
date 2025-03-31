#include <iostream>

class ICloneable {
public:
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() {}
};

template <typename T>
struct ValueHolder : public ICloneable {
    T data_;

    ValueHolder(const T& data) : data_(data) {}

    ICloneable* clone() const override {
        return new ValueHolder<T>(*this);
    }
};

int main() {
    ValueHolder<int> intHolder(42);
    ICloneable* clonedIntHolder = intHolder.clone();

    ValueHolder<int>* clonedInt = dynamic_cast<ValueHolder<int>*>(clonedIntHolder);
    if (clonedInt) {
        std::cout << "Cloned int value: " << clonedInt->data_ << std::endl;
    }

    delete clonedIntHolder;

    ValueHolder<std::string> stringHolder("Hello, World!");
    ICloneable* clonedStringHolder = stringHolder.clone();

    ValueHolder<std::string>* clonedString = dynamic_cast<ValueHolder<std::string>*>(clonedStringHolder);
    if (clonedString) {
        std::cout << "Cloned string value: " << clonedString->data_ << std::endl;
    }

    delete clonedStringHolder;

    return 0;
}
