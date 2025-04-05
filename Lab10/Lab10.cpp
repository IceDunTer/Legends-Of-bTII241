#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>
#include <mutex>
#include <locale>

using namespace std;

mutex mtx; //Мьютекс для синхронизации вывода

//Ф-ция для умножения строки матрицы на вектор
void multiplyRow(const vector<vector<int>>& matrix, const vector<int>& vect, vector<int>& result, int row, int priority) {

    SetThreadPriority(GetCurrentThread(), priority); 

    int sum = 0; //Сумма, получившаяся в результате умножения строки
    for (size_t i = 0; i < vect.size(); ++i) {
        sum += matrix[row][i] * vect[i];
        lock_guard<mutex> lock(mtx);
        cout << "Поток " << row << " выполняет шаг " << i << "...\n"; 
        this_thread::sleep_for(chrono::milliseconds(100)); //Задержка для визуализации
    }

    lock_guard<mutex> lock(mtx);
    cout << "Поток " << row << " завершил вычисление.\n";

    result[row] = sum;
}

//Ввод вектора
vector<int> inputVector(size_t size) {
    vector<int> vec(size);
    cout << "Введите элементы вектора (" << size << " элемента(-ов)):\n";
    for (size_t i = 0; i < size; ++i) {
        cout << "Элемент " << i+1 << ": ";
        cin >> vec[i];
    }
    cout << "\n";
    return vec;
}

//Ввод приоритетов потока
vector<int> inputPriorities(size_t size) {
    vector<int> priors(size);
    cout << "Введите приоритеты потоков (0 - ниже нормы, 1 - нормальный, 2 - высший):\n";
    for (size_t i = 0; i < size; ++i) {
        int priority;
        cout << "Приоритет потока " << i << ": ";
        cin >> priority;
        switch (priority) {
        case 0:
            priors[i] = THREAD_PRIORITY_BELOW_NORMAL;
            break;
        case 1:
            priors[i] = THREAD_PRIORITY_NORMAL;
            break;
        case 2:
            priors[i] = THREAD_PRIORITY_HIGHEST;
            break;
        default:
            cout << "Некорректный приоритет. Установлен нормальный приоритет.\n";
            priors[i] = THREAD_PRIORITY_NORMAL;
            break;
        }
    }
    cout << "\n";
    return priors;
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<int> vec = inputVector(matrix[0].size()); //Запись вектора в переменную vec
    vector<int> priors = inputPriorities(matrix.size()); //Запись приоритетов в priors
    vector<int> res(matrix.size()); //Запись результатов умножения
    vector<thread> ths;

    for (size_t i = 0; i < matrix.size(); ++i) {
        //Создаем поток и записываем его
        ths.emplace_back(multiplyRow, ref(matrix), ref(vec), ref(res), i, priors[i]);
    }

    for (auto& th : ths) {
        th.join(); //Ожидание завершения всех потоков
    }
    
    //Вывод результата
    cout << "Результат умножения матрицы на вектор:\n";
    for (const auto& r : res) {
        cout << r << "\n";
    }
    return 0;
}
