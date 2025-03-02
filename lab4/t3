#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#define _CRT_SECURE_NO_DEPRECATE

struct AEROFLOT {
    int NUMR;
    float COST;
    char NAZN[50];
    char TIP[20];
};
void main() {
    setlocale(LC_ALL, "RUS");
    AEROFLOT mass[7];
    char s[15];
    std::cout << "Введите данные о самолетах" << std::endl;
    for (int i = 0; i < 7; i++) {
        std::cout << "Введите данные о самолете (цена, назначение, тип)" << std::endl;
        mass[i].NUMR = i;
        std::cin >> mass[i].COST >> mass[i].NAZN >> mass[i].TIP;
    }
    std::cout << "Искомый пункт назначения" << std::endl;
    std::cin >> s;
    int cnt = 0;
    for (int i = 0; i < 7; i++) {
        if (strcmp(mass[i].NAZN, s)==0) {
            cnt++;
            std::cout << mass[i].NUMR << " " << mass[i].TIP << std::endl;
        }
    }
    if (cnt == 0) printf("Рейсов в %s нет", s);
}
