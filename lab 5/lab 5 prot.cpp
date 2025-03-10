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
void main() {
	setlocale(LC_ALL, "ru");
	cout << "выберите действие\n" << "1. ввод значений для x и y\n" << "2. обнулить значения x и y\n" << "3. расчитать растояние от начала кординатной плоскости до точки" << endl;
	int choise;
	cin >> choise;
	point tocka;
	switch (choise)
	{
	case 1: 
		cin >> tocka.x;
		cin >> tocka.y;
		cout << "значение x " << tocka.x << "\nзначение y " << tocka.y << endl;
	case 2:
		tocka.zero();
	case 3:
		tocka.range();
	}

}