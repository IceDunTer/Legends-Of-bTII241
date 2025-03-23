#include <iostream>
#include <math.h>
#include <locale.h>
#include <time.h>
using namespace std;

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	int const n = 10;
	int mass[n], vibor;
	float s = 0; // сумма чисел
	std::cout << "Заполнение ручками - 1, заполнение случайными числами - 2" << std::endl;
	std::cin >> vibor;
	switch (vibor)
	{
	case 1:
		for (int i = 0; i < n; i++)
		{
			cout << "arr[" << i << "] = ";
			cin >> mass[i];
			s += mass[i];
		}
	case 2:
		for (int i = 0; i < n; i++)
		{
			mass[i] = rand()%20;
			cout << "arr[" << i << "] = " << mass[i] << std::endl;
			s += mass[i];
		}
	default:
		break;
	}
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (mass[i] > max) {
			max = mass[i];
		}
	}
	float result = s / n;
	cout << "Макс число = " << max << endl;
	printf("среднее арифметическое = %lg\n", result);
	for (int i = n - 1; i >= 0; i--)
		cout << mass[i] << " ";

	return 0;
}
