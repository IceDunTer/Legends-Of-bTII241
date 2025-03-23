#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale>
#include <sstream>
using namespace std;


int countWords(const string& line) {
    istringstream stream(line);
    string word;
    int count = 0;
    while (stream >> word) {
        count++;
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "RUS");
    FILE* inputFile = fopen("input_lab4_2.txt", "r");
    FILE* outputFile = fopen("output_lab4_2.txt", "w");

    if (!inputFile) {
        perror("Ошибка открытия файла input.txt");
        return 1;
    }

    if (!outputFile) {
        perror("Ошибка открытия файла output.txt");
        fclose(inputFile);
        return 1;
    }

    char line[1024]; // Буфер для чтения строки
    while (fgets(line, sizeof(line), inputFile)) {
        int wordCount = countWords(line);
        fprintf(outputFile, "%s (%i)\n", line, wordCount);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
