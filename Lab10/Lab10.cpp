#include <iostream>
#include <thread> // Потоки
#include <vector> // Динамические массивы
using namespace std;

// Вывод матрицы. Ф-ция выполняющаяся в потоке
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // Создаем двумерный вектор (динамический массив, или матрица) с элем. типа "int"
    vector<vector<int>> matrix = { 
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Поток матрицы, в котором выполняется ф-ция printMatrix
    thread matrixThread(printMatrix, matrix);
    cout << "Основной поток продолжает выполнение..." << endl;
    
    // Завершение потока
    matrixThread.join();
    cout << "Основной поток завершен." << endl;
    return 0;
}
