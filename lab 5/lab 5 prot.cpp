#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

class point {
public:
	int x, y, a;
	void zero() {
		cout << "��������� x � y ";
		x = 0;
		y = 0;
		cout << "�������� x " << x << "\n�������� y " << y << endl;
	}
	
	void range() {
		double rast;
		rast = sqrt(x + y);
		cout << "���������� �� ������ �������� �� ������ = " << rast << endl;
	}
};
void main() {
	setlocale(LC_ALL, "ru");
	cout << "�������� ��������\n" << "1. ���� �������� ��� x � y\n" << "2. �������� �������� x � y\n" << "3. ��������� ��������� �� ������ ����������� ��������� �� �����" << endl;
	int choise;
	cin >> choise;
	point tocka;
	switch (choise)
	{
	case 1: 
		cin >> tocka.x;
		cin >> tocka.y;
		cout << "�������� x " << tocka.x << "\n�������� y " << tocka.y << endl;
	case 2:
		tocka.zero();
	case 3:
		tocka.range();
	}

}