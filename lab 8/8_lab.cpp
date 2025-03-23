#include <iostream>
#include <cmath>
#include <locale>
#include <stdexcept>
using namespace std;

#define _CRT_SECURE_NO_DEPRECATE

int main() {
    setlocale(LC_ALL, "ru");
    double ex, y;
    cout << "Введите число для извлечения корня:" << endl;
    cin >> y;

    try {
        if (y < 0) {
            throw logic_error("Нельзя извлечь корень из отрицательного числа.");
        }
        ex = sqrt(y);
        cout << "Результат = " << ex << endl;
    }
    catch (logic_error& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}