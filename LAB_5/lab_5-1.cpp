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
		cout << "расстояние от начала кординат до точнки = " << rast << endl;
	}
	point ()
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
};


int main() {
	setlocale(LC_ALL, "ru");
	point tocka;
	int choice;
	while (true) {
		cout << "выберите действие\n" << "1. ввод значений для x и y\n" << "2. перемещение в начало кординат x и y\n" << "3. расчитать растояние от начала кординатной плоскости до точки\n" << "4. вывод значений x и y\n" << "0. Выход" << endl << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\nВы выбрали опцию 1.\n" << "введитезначение X: ";
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
