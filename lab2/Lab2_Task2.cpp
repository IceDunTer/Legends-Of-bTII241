#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iomanip>
#define _CRT_SECURE_NO_DEPRECATE
int main() {
	setlocale(LC_ALL, "RUS");
	int massiv[4][6];
	int g, sravn;
	std::cout << "Введите числа массива" << std::endl;
	for (int stol = 0; stol < 4; stol++) {
		for (int str = 0; str < 6; str++) {
			std::cin >> g;
			massiv[stol][str] = g;
		}
	}
	for (int stol = 0; stol < 4; stol++) {
		for (int str = 0; str < 6; str++) {
			std::cout << std::setw(5) << massiv[stol][str] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "Введите число для сравнения" << std::endl;
	std::cin >> sravn;
	int massiv1[4], cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (massiv[i][j] > sravn) cnt++;
		}
		massiv1[i] = cnt;
		cnt = 0;
	}
	for (int i = 0; i < 4; i++) std::cout << std::setw(5) << massiv1[i];
}
