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
		cout << "����������� � ������ �������� x � y ";
		x = 0;
		y = 0;
		cout << "�������� x " << x << "\n�������� y " << y << endl;
	}

	void range() {
		double rast;
		rast = sqrt(x + y);
		cout << "���������� �� ������ �������� �� ������ = " << rast << endl;
	}
	point ()
	{
		x = 0;
		y = 0;
		cout << "�������� �� ����\n" << endl;
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
		cout << "�������� ��������\n" << "1. ���� �������� ��� x � y\n" << "2. ����������� � ������ �������� x � y\n" << "3. ��������� ��������� �� ������ ����������� ��������� �� �����\n" << "4. ����� �������� x � y\n" << "0. �����" << endl << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\n�� ������� ����� 1.\n" << "��������������� X: ";
			cin >> tocka.x;
			cout << "��������������� y: ";
			cin >> tocka.y;
			break;
		case 2:
			cout << "\n�� ������� ����� 2.\n" << endl;
			tocka.zero();
			break;
		case 3:
			cout << "\n�� ������� ����� 3.\n" << endl;
			tocka.range();
			break;
		case 4:
			cout << "\n�� ������� ����� 4.\n" << endl;
			tocka.print();
			break;
		case 0:
			cout << "\n����� �� ���������.\n";
			return 0;
			break;
		default:
			cout << "\n������������ �����, ���������� �����.\n";
			break;
		}


	}

}