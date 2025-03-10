#include <iostream>
#include <string>
#include <locale.h>
#include <cmath>
using namespace std;

class point {
public:
    int x, y;

    void print() {
        cout << "x: " << x << "\ty: " << y << endl;
    }

    void zero() {
        cout << "перемещение в начало координат x и y ";
        x = 0;
        y = 0;
        cout << "значение x " << x << "\nзначение y " << y << endl;
    }

    void range() {
        double rast;
        rast = sqrt(x * x + y * y);
        cout << "расстояние от начала координат до точки = " << rast << endl;
    }

    point() {
        x = 0;
        y = 0;
        cout << "значения на нуле\n" << endl;
    }

    point(int raw_x, int raw_y) {
        x = raw_x;
        y = raw_y;
    }

    void vect(int xr, int yr) {
        x += xr;
        y += yr;
    }

    int ravno() {
        return x == y;
    }

    void ymn(int xr) {
        x *= xr;
        y *= xr;
    }

    void binn(int xr) {
        x += xr;
        y += xr;
    }

    int inde(int index) {
        if (index == 0) {
            return x;
        }
        else if (index == 1) {
            return y;
        }
        else {
            cout << "Некорректный индекс. Допустимые значения: 0 или 1." << endl;
            return -1;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    point tocka;
    int choice, a = 0, b = 0, ind = 0;
    while (true) {
        cout << "выберите действие\n"
            << "1. ввод значений для x и y\n"
            << "2. перемещение в начало координат x и y\n"
            << "3. рассчитать расстояние от начала координатной плоскости до точки\n"
            << "4. вывод значений x и y\n"
            << "5. переместиться на вектор\n"
            << "6. Увеличить обе координаты на 1\n"
            << "7. Уменьшить обе координаты на 1\n"
            << "8. Проверка равенства координат\n"
            << "9. Умножение координат на скаляр\n"
            << "10. Бинарный +-\n"
            << "11. Индексатор\n"
            << "0. Выход" << endl << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "\nВы выбрали опцию 1.\n" << "введите значение X: ";
            cin >> tocka.x;
            cout << "введите значение y: ";
            cin >> tocka.y;
            break;
        case 2:
            cout << "\nВы выбрали опцию 2.\n" << endl;
            tocka.zero();
            break;
        case 3:
            cout << "\nВы выбрали опцию 3.\n" << endl;
            tocka.range();
            break;
        case 4:
            cout << "\nВы выбрали опцию 4.\n" << endl;
            tocka.print();
            break;
        case 5:
            cout << "\nВы выбрали опцию 5." << "\nВведите значения x" << endl;
            cin >> a;
            cout << "\nВведите значение y" << endl;
            cin >> b;
            tocka.vect(a, b);
            break;
        case 6:
            cout << "\nВы выбрали опцию 6." << endl;
            tocka.vect(1, 1);
            break;
        case 7:
            cout << "\nВы выбрали опцию 7." << endl;
            tocka.vect(-1, -1);
            break;
        case 8:
            cout << "\nВы выбрали опцию 8." << "\nВведите значения скаляра" << endl;
            cin >> a;
            tocka.ymn(a);
            break;
        case 9:
            cout << "\nВы выбрали опцию 9." << "\nВведите значения скаляра" << endl;
            cin >> a;
            tocka.binn(a);
            break;
        case 10:
            cout << "\nВы выбрали опцию 10." << "\nВведите индекс (0 для x, 1 для y)" << endl;
            cin >> ind;
            int cord = tocka.inde(ind);
            if (cord != -1) {
                cout << "Значение координаты: " << cord << endl;
            }
            break;
        case 0:
            cout << "\nВыход из программы.\n";
            return 0;
        default:
            cout << "\nНекорректный выбор, попробуйте снова.\n";
            break;
            a = 0, b = 0, ind = 0;
        }
    }
}
