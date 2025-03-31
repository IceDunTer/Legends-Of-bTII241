#include <iostream>
#include <stdexcept>

struct ICloneable {
    virtual ~ICloneable() = default;
    virtual ICloneable* clone() const = 0;
};

template <typename T>
struct ValueHolder : ICloneable {
    T data_;

    explicit ValueHolder(const T& value) : data_(value) {}

    ICloneable* clone() const override {
        return new ValueHolder(data_);
    }
};

class Any {
public:
    Any() : data_(nullptr) {}

    template <typename T>
    Any(const T& value) : data_(new ValueHolder<T>(value)) {}

    Any(const Any& other) : data_(other.data_ ? other.data_->clone() : nullptr) {}

    ~Any() {
        delete data_;
    }

    Any& operator=(const Any& other) {
        if (this != &other) {
            delete data_;
            data_ = other.data_ ? other.data_->clone() : nullptr;
        }
        return *this;
    }

    template <typename T>
    Any& operator=(const T& value) {
        delete data_;
        data_ = new ValueHolder<T>(value);
        return *this;
    }

    template <typename T>
    T* cast() {
        if (!data_) return nullptr;
        ValueHolder<T>* holder = dynamic_cast<ValueHolder<T>*>(data_);
        return holder ? &holder->data_ : nullptr;
    }

private:
    ICloneable* data_;
};

int main() {
    Any a(10);
    int* pi = a.cast<int>();
    if (pi) std::cout << "int: " << *pi << std::endl;

    Any b = 3.14;
    double* pd = b.cast<double>();
    if (pd) std::cout << "double: " << *pd << std::endl;

    Any c = std::string("hello");
    std::string* ps = c.cast<std::string>();
    if (ps) std::cout << "string: " << *ps << std::endl;

    Any empty;
    int* p = empty.cast<int>();
    if (!p) std::cout << "empty is empty" << std::endl;

    return 0;
}
