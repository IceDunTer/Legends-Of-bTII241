#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

class point {
public:
	int x, y, a;
	void zero() {
		cout << "обнуление x и y ";
		x = 0;
		y = 0;
		cout << "значение x " << x << "\nзначение y " << y << endl;
	}
	
	void range() {
		double rast;
		rast = sqrt(x + y);
		cout << "расстояние от начала кординат до точнки = " << rast << endl;
	}
};
void option1() {
	cout << "Вы выбрали опцию 1.\n";
	cin << tocka.x;
	cin << tocka.y;
}

void option2() {
	cout << "Вы выбрали опцию 2.\n";
	tocka.zero();
}

void option3() {
	cout << "Вы выбрали опцию 3.\n";
	tocka.range();

}

void main() {
	setlocale(LC_ALL, "ru");
	cout << "выберите действие\n" << "1. ввод значений для x и y\n" << "2. обнулить значения x и y\n" << "3. расчитать растояние от начала кординатной плоскости до точки" << "0. Выход" << endl;
	point tocka;
	
	int choice;

	do {
		cin >> choice;

		switch (choice) {
		case 1:
			option1();
			break;
		case 2:
			option2();
			break;
		case 3:
			option3();
			break;
		case 0:
			cout << "Выход из программы.\n";
			break;
		default:
			cout << "Некорректный выбор, попробуйте снова.\n";
			break;
		}
	

	} while (choice != 0);

	return 0;
}