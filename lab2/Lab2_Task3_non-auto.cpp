#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_DEPRECATE
using namespace std;

void fillArray(int arr[], int n) {
	cout << "Введите числа через Enter:\n";
	int j;
	for (int i = 0; i < n; i++) {
		scanf_s("%i", &j);
		arr[i] = j;
	}
}

void sortArray(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIndex]) minIndex = j;
		}
		int temp = arr[minIndex];
		arr[minIndex] = arr[i];
		arr[i] = temp;
	}
}

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%i, ", arr[i]);
	}
	printf("\n");
}

void main() {
	setlocale(LC_ALL, "RUS");
	int arr[1000];
	int n;
	cout << "Введите кол-во символов в массиве:\n";
	scanf_s("%i", &n);
	fillArray(arr, n); // заполнение массива
	printArray(arr, n);

	sortArray(arr, n); // сортировка массива
	printArray(arr, n);



}
