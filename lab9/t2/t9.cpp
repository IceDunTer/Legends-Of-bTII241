#include <iostream>
#include <cstddef>
template <typename T>
void array_size(const T&) {
    static_assert(sizeof(T) == 0, "Ne massiv");
}

template <typename T, size_t N>
size_t array_size(T(&)[N]) {
    return N;
}
int main() {
    int ints[] = { 1, 2, 3, 4 };
    double doubles[] = { 3.14 };
    int* iptr = ints;

    std::cout << array_size(ints) << "\n";
    std::cout << array_size(doubles) << "\n";
    //oshibka
    //array_size(iptr);
    return 0;
}
