#include<iostream>
using namespace std;
#include<locale.h>
#include<cmath>
#include <iomanip>
#include<string>
int main() {
    setlocale(LC_ALL, "ru");
    string str;

    cout << "������� ������: ";
    getline(cin, str);

    for (int i = 0; i < str.rfind("quit"); i++)
    {
        if (str[i] == ' ')
        {
            str[i] = '!';
        }
    }

    cout << str << endl;
}