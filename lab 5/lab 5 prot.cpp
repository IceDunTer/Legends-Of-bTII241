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
void option1() {
	cout << "�� ������� ����� 1.\n";
	cin << tocka.x;
	cin << tocka.y;
}

void option2() {
	cout << "�� ������� ����� 2.\n";
	tocka.zero();
}

void option3() {
	cout << "�� ������� ����� 3.\n";
	tocka.range();

}

void main() {
	setlocale(LC_ALL, "ru");
	cout << "�������� ��������\n" << "1. ���� �������� ��� x � y\n" << "2. �������� �������� x � y\n" << "3. ��������� ��������� �� ������ ����������� ��������� �� �����" << "0. �����" << endl;
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
			cout << "����� �� ���������.\n";
			break;
		default:
			cout << "������������ �����, ���������� �����.\n";
			break;
		}
	

	} while (choice != 0);

	return 0;
}