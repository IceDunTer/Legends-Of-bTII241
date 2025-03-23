#include <iostream>
#include <cmath>
#include <locale>
#include <stdexcept>
using namespace std;

#define _CRT_SECURE_NO_DEPRECATE

int main() {
    setlocale(LC_ALL, "ru");
    double ex, y;
    cout << "������� ����� ��� ���������� �����:" << endl;
    cin >> y;

    try {
        if (y < 0) {
            throw logic_error("������ ������� ������ �� �������������� �����.");
        }
        ex = sqrt(y);
        cout << "��������� = " << ex << endl;
    }
    catch (logic_error& e) {
        cout << "������: " << e.what() << endl;
    }

    return 0;
}