#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_DEPRECATE
using namespace std;
void task1(){
	//исходные 1,1 2,2 результат 0,001481
	float a, b, y;
	printf("Введите число a и b\n");
	scanf_s("%f", &a);
	printf("\n");
	scanf_s("%f", &b);
	y = pow(sin(a + pow(b, 3)), 2) * sqrt((exp(a * a - 9.4)) / (pow((a + b), 3)));
	printf("Результат операции при А=%f и B=%f равен %f", a, b, y);
}
void task2() {
	float a, b = 1.0;
	double y, z;
	printf("Введите число x\n");
	scanf_s("%f", &a);
	y = a;
	z = a * a;
	b = 1 - y + z;
	while (abs((y - z)) > 0.001) {
		y *= a * a;
		z *= a * a;
		//printf("%f %f\n", b, (-1) * y);
		b += (-1) * y;
		//printf("%f %f\n", b, z);
		b += z;
	}
	printf("Результат %f\n", b);
	//printf("a=%lf b=%lf\n", y, z);
}
void task3_1() {
	int n, j;
	cout << 'n' << endl;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		if (n % i == 0) {
			j = i;
			cout << j << endl;
		}
	}
}
void task3_2() {
	float a, a1 = 1, a2 = 2, min, max, res;
	float i;
	cout << "a1=, a2=" << endl;
	cin >> a1;
	cin >> a2;
	if (a1 > a2) {
		max = a1;
		min = a2;
	}
	else {
		min = a1;
		max = a2;
	}
	i = 3;
	while (i < 100.) {
		cout << 'a' << "= " << i << endl;
		a = i;
		if (a < min) min = a;
		if (a > max) max = a;
		i++;
	}
	printf("%f %f\n", min, max);
	res = max - min;
	cout << res;
}
void task3_3() {
	int n, y;
	cin >> n;
	if (n % 2 != 0) {
		y = 1;
		for (int i = 1; i <= n; i += 2) {
			y *= i;
		}
	}
	else {
		y = 1;
		for (int i = 2; i <= n; i += 2) {
			y *= i;
		}
	}
	cout << y << endl;
}
void task4_4() {
	int x, m, n, k;
	float s, rez = 0, resz = 0;
	cout << "n: x:" << endl;
	scanf_s("%i", &n);
	scanf_s("%i", &x);
	for (k = 1; k <= n; k++) {
		for (m = k; m <= n; m++) {
			s = (x + k) / float(m);
			printf("%f\n", s);
			rez += s;
		}
	}
	cout << rez << endl;
}
void task3_5() {
	int i, n, j;
	float s = 0;
	cin >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++)
			s += 1 / (float(i) + 2 * j);
	cout << s << endl;
}
void task3_6() {
	int fac = 1;
	float zn = 0, s;
	for (int k = 1; k <= 10; k++) {
		s = 0;
		fac = 1;
		for (int n = 1; n <= k; n++) {
			s += sin(float(k) * n);
			fac *= n;
		}
		zn += float(s) / fac;
	}
	cout << zn << endl;
}
void task3_7() {
	int n, i, s, sum = 0;
	cout << "enter n" << endl;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		s = i * i * i + 3 * i * n * n + n;
		if (s % 3 == 0) {
			int k = s / 3;
			if (k % 2 != 0) sum += s;
		}
	}
	cout << sum << endl;
}
void task4() {
	float n = 0;
	cout << "enter n" << endl;
	cin >> n;
	n = abs(n);
	cout << "Модуль числа=" << n << endl;
}
int main() {
	setlocale(LC_ALL, "RUS");
	int x = 0, vibor1 = 0;
	printf("Введите номер задания\n");
	cin >> x;
	setlocale(LC_ALL, "RUS");
	switch (x)
	{
	case 1:
		task1();
		break;
	case 2:
		task2();
		break;
	case 3:
		printf("Введите номер задания в задание 3\n");
		cin >> vibor1;
		switch (vibor1)
		{
		case 1:
			task3_1();
			break;
		case 2:
			task3_2();
			break;
		case 3:
			task3_3();
			break;
		case 4:
			task4_4();
			break;
		case 5:
			task3_5();
			break;
		case 6:
			task3_6();
			break;
		case 7:
			task3_7();
			break;
		default:
			break;
		}
		break;
	case 4:
		task4();
		break;
	default:
		break;
	}

}
