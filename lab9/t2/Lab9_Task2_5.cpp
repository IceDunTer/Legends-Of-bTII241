#include <iostream>
#include <cstddef>
#include <algorithm> // Для std::swap

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

template <typename T, typename Comparator>
T minimum(const Array<T>& array, Comparator comp) {
    if (array.size() == 0) {
        throw std::invalid_argument("Array is empty");
    }

    T min_value = array[0];
    for (size_t i = 1; i < array.size(); ++i) {
        if (comp(array[i], min_value)) {
            min_value = array[i];
        }
    }
    return min_value;
}

bool less(int a, int b) {
    return a < b;
}

struct Greater {
    bool operator()(int a, int b) {
        return b < a;
    }
};

int main() {
    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;

    int min = minimum(ints, less);
    std::cout << "Minimum value: " << min << std::endl;

    int max = minimum(ints, Greater());
    std::cout << "Maximum value: " << max << std::endl;

    return 0;
}
