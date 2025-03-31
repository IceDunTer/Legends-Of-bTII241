#include <cstddef>
#include <iostream>
#include <iomanip>
template <typename T, typename U>
void copy_n(T* destination, const U* source, std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        destination[i] = static_cast<T>(source[i]);
    }
}

int main() {
    int ints[] = { 1, 2, 3, 4 };
    double doubles[4] = {};
    copy_n(doubles, ints, 4);
    std::cout << std::fixed << std::setprecision(1);
    for (int i = 0; i < 4;i++) {
        std::cout << doubles[i] << " ";
    }
    return 0;
}
