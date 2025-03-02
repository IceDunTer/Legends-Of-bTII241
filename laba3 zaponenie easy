#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#define _CRT_SECURE_NO_DEPRECATE

void outmas2(int razm, int massiv[][16]) {
    for (int i = 0; i < razm; i++) {
        for (int j = 0; j < razm; j++) {
            if (massiv[i][j] != -858993460) std::cout << std::setw(5) << massiv[i][j];
            else std::cout << std::setw(3) << 0;
        }
        std::cout << std::endl;
    }
}

// Функция для получения определителя матрицы
double opred(int matrix[][16], int n) {
    if (n == 1) return matrix[0][0];
    if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double det = 0;
    for (int i = 0; i < n; i++) {
        int submatrix[16][16];
        for (int j = 1; j < n; j++) {
            int m = 0;
            for (int k = 0; k < n; k++) {
                if (k == i) continue;
                submatrix[j - 1][m] = matrix[j][k];
                m++;
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * opred(submatrix, n - 1);
    }
    return det;
}

// Функция для получения матрицы миноров
void minorMat(int matrix[][16], int min[][16], int n) {
    if (n == 1) {
        min[0][0] = 1;
        return;
    }
    int sign = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int submatrix[16][16];
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (k != i && l != j) {
                        submatrix[k < i ? k : k - 1][l < j ? l : l - 1] = matrix[k][l];
                    }
                }
            }
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            min[j][i] = sign * opred(submatrix, n - 1);
        }
    }
}

// Функция для получения обратной матрицы
void obrmat(int matrix[][16], int n) {
    double det = opred(matrix, n);
    if (det == 0) {
        std::cout << "Обратная матрица не существует." << std::endl;
        return;
    }
    int min[16][16];
    minorMat(matrix, min, n);
    std::cout << "Обратная матрица:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << std::setw(3) << min[i][j]/det << " ";
        }
        std::cout << std::endl;
    }
}

// Функция для умножения двух матриц
void ymnmat(int matrix1[][16], int matrix2[][16], int n) {
    int result[16][16];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] = matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    std::cout << "Результирующая матрица:" << std::endl;
    outmas2(n, result);
}

void main() {
    setlocale(LC_ALL, "RUS");
    int massiv[16][16], g, vibor1, vibor2=0;
    std::cout << "Введите сторону матрицы" << std::endl;
    std::cin >> g;
    int cnt = g - 1, cnt1 = 1, cnt2 = 1, i = 0, j = 0, krug = 1;
    for (i; i < g / 2; i += cnt1) {
        for (j = i; j < g - i; j += cnt1) {
            massiv[i][j] = cnt2;
            outmas2(g, massiv);
            if ((j != i) && (j != cnt)) massiv[j][cnt] = cnt2 + (cnt - i) * 1;
            outmas2(g, massiv);
            if (cnt < g - 1) massiv[cnt][cnt - j + (g - 1 - cnt)] = cnt2 + (cnt - i) * 2;
            else massiv[cnt][cnt - j] = cnt2 + (cnt - i) * 2;
            outmas2(g, massiv);
            if (cnt < g - 1) { if ((j != i) && (j != cnt)) massiv[cnt - j + (g - 1 - cnt)][i] = cnt2 + (cnt - i) * 3; }
            else { if ((j != i) && (j != cnt)) massiv[cnt - j][i] = cnt2 + (cnt - i) * 3; }
            outmas2(g, massiv);
            cnt2++;
        }
        cnt2 = cnt * 4 * krug + 1;
        if (g % 2 != 0) massiv[g / 2][g / 2] = g * g;
        krug += 1;
        cnt -= 1;
    }
    outmas2(g, massiv);
    std::cout << "1 - обратная матрица, 2 - умножение матриц" << std::endl;
    std::cin >> vibor1;
    switch (vibor1)
    {
    case 1:
        int massiv3[16][16];
        std::cout << "Обратная матрица для заполненной(1) или для новой(2)" << std::endl;
        std::cin >> vibor2;
        if (vibor2 == 1) obrmat(massiv, g);
        else {
            std::cout << "Введите элементы матрицы:" << std::endl;
            for (int i = 0; i < g; i++) {
                for (int j = 0; j < g; j++) {
                    std::cin >> massiv3[i][j];
                }
            }
            obrmat(massiv3, g);
        }
        break;
    case 2:
        int massiv2[16][16];
        std::cout << "Введите элементы второй матрицы:" << std::endl;
        for (int i = 0; i < g; i++) {
            for (int j = 0; j < g; j++) {
                std::cin >> massiv2[i][j];
            }
        }
        ymnmat(massiv, massiv2, g);
        break;
    default:
        std::cout << "Неверный выбор." << std::endl;
        break;
    }
}
