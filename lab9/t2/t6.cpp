#include <iostream>
#include <cstddef>
#include <algorithm> // для fill и copy
#include <type_traits> // для std::enable_if и std::is_same

template <typename T>
class Array {
public:
    explicit Array(size_t size = 0, const T& value = T())
        : size_(size), data_(size ? new T[size] : nullptr) {
        if (data_) {
            std::fill(data_, data_ + size_, value);
        }
    }

    Array(const Array& other)
        : size_(other.size_), data_(size_ ? new T[size_] : nullptr) {
        if (data_) {
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }

    ~Array() {
        delete[] data_;
    }

    Array& operator=(Array other) {
        swap(other);
        return *this;
    }

    void swap(Array& other) {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    size_t size() const {
        return size_;
    }

    T& operator[](size_t idx) {
        return data_[idx];
    }

    const T& operator[](size_t idx) const {
        return data_[idx];
    }

private:
    size_t size_;
    T* data_;
};

template <typename T>
void flatten_element(const T& element, std::ostream& out);

template <typename T>
void flatten_element(const Array<T>& element, std::ostream& out);

template <typename T>
void flatten(const Array<T>& array, std::ostream& out) {
    for (size_t i = 0; i < array.size(); ++i) {
        flatten_element(array[i], out);
    }
}

// обработка
template <typename T>
void flatten_element(const T& element, std::ostream& out) {
    out << element << " ";
}

// если массив
template <typename T>
void flatten_element(const Array<T>& element, std::ostream& out) {
    flatten(element, out);
}

int main() {
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout);
    std::cout << std::endl;

    Array<Array<int>> array_of_ints(2, ints);
    flatten(array_of_ints, std::cout);
    std::cout << std::endl;

    Array<double> doubles(10, 0.0);
    flatten(doubles, std::cout);
    std::cout << std::endl;

    return 0;
}
