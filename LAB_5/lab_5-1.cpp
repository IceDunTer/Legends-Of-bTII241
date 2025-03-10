#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

class point {
public:
	int x, y;
	void print() {
		cout << "x: " << x << "\ty: " << y << endl;

	}
	void zero() {
		cout << "перемещение в начало кординат x и y ";
		x = 0;
		y = 0;
		cout << "значение x " << x << "\nзначение y " << y << endl;
	}

	void range() {
		double rast;
		rast = sqrt(x + y);
		cout << "расстояние от начала кординат до точки = " << rast << endl;
	}
	point()
	{
		x = 0;
		y = 0;
		cout << "значения на нуле\n" << endl;
	}
	point(int raw_x, int raw_y)
	{
		x = raw_x;
		y = raw_y;
	}
	void vect(int xr, int yr) {
		x += xr;
		y += yr;
	}
	int ravno() {
		if (x == y) return 1;
		else return 0;
	}
	void ymn(int xr) {
		x *= xr;
		y *= xr;
	}
	void binn(int xr) {
		x += xr;
		y += xr;
	}
};


int main() {
	setlocale(LC_ALL, "ru");
	point tocka;
	int choice, a =0 , b=0;
	while (true) {
		cout << "выберите действие\n" << "1. ввод значений для x и y\n" << "2. перемещение в начало кординат x и y\n" << "3. расчитать растояние от начала кординатной плоскости до точки\n" << "4. вывод значений x и y\n" << "5. переместиться на вектор\n" << "6. Увеличить обе координаты на 1\n" << "7. Уменьшить обе координаты на \n"<<"8. Проверка равенства координат\n"<<"8. Умножение координат на скаляр\n"<<"9. Бинарный +-\n" << "0. Выход" << endl << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\nВы выбрали опцию 1.\n" << "введите значение X: ";
			cin >> tocka.x;
			cout << "введитезначение y: ";
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
			cout << "\nВведите значение у" << endl;
			cin >> b;
			tocka.vect(a, b);
			break;
		case 6:
			cout << "\nВы выбрали опцию 6."<< endl;
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
		case 0:
			cout << "\nВыход из программы.\n";
			return 0;
			break;
		default:
			cout << "\nНекорректный выбор, попробуйте снова.\n";
			break;
		}


	}

}
