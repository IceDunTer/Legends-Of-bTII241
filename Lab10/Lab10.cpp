#include <windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <locale>

using namespace std;

// Структура для передачи данных в поток
struct ThreadData {
    vector<int> row;        // Строка матрицы
    vector<int> vector;     // Вектор
    int priority;           // Приоритет потока
    int thread_id;          // Идентификатор потока
    int result;             // Результат умножения
    bool completed;         // Флаг завершения
    HANDLE hMutex;          // Мьютекс для синхронизации вывода
    string priority_name;   // Название приоритета
};

vector<ThreadData*> all_threads;

void setCursorPos(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

DWORD WINAPI multiply_row(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;

    SetThreadPriority(GetCurrentThread(), data->priority);

    data->result = 0;
    for (size_t i = 0; i < data->row.size(); ++i) {
        data->result += data->row[i] * data->vector[i];

        WaitForSingleObject(data->hMutex, INFINITE);

        setCursorPos(5, data->thread_id + 8);
        cout << "Поток " << data->thread_id << " (" << data->priority_name << "): [";
        for (size_t j = 0; j < data->row.size(); ++j) {
            if (j <= i) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Красный
                cout << "#";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Белый
            }
            else {
                cout << " ";
            }
        }
        cout << "] " << (i + 1) * 100 / data->row.size() << "%";

        ReleaseMutex(data->hMutex);

        Sleep(200); // Задержка для наглядности
    }

    data->completed = true;
    return 0;
}

void display_threads_status() {
    system("cls");
    cout << "Многопоточное умножение матрицы на вектор (Windows API)\n";
    cout << "=====================================================\n\n";
    cout << "Доступные приоритеты потоков:\n";
    cout << "1. Idle (низший)\n";
    cout << "2. Below Normal\n";
    cout << "3. Normal\n";
    cout << "4. Above Normal\n";
    cout << "5. Highest (высший)\n\n";

    for (size_t i = 0; i < all_threads.size(); ++i) {
        ThreadData* data = all_threads[i];

        cout << "Поток " << data->thread_id << ": " << setw(14) << left << data->priority_name << " | ";

        if (data->completed) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Зеленый
            cout << "Завершен. Результат: " << data->result;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Белый
        }
        else {
            cout << "Выполняется...";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

    int size;
    cout << "Введите размер квадратной матрицы (количество строк): ";
    cin >> size;

    vector<vector<int>> matrix(size, vector<int>(size));
    vector<int> vec(size);

    cout << "\nВведите элементы матрицы:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << "matrix[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }

    cout << "\nВведите элементы вектора:\n";
    for (int j = 0; j < size; ++j) {
        cout << "vector[" << j << "] = ";
        cin >> vec[j];
    }

    struct {
        int value;
        string name;
    } priorities[] = {
        {THREAD_PRIORITY_IDLE, "Idle"},
        {THREAD_PRIORITY_BELOW_NORMAL, "Below Normal"},
        {THREAD_PRIORITY_NORMAL, "Normal"},
        {THREAD_PRIORITY_ABOVE_NORMAL, "Above Normal"},
        {THREAD_PRIORITY_HIGHEST, "Highest"}
    };

    vector<int> thread_priority_indices(size);
    for (int i = 0; i < size; ++i) {
        int choice;
        do {
            cout << "\nВыберите приоритет для потока " << i << " (1-5):\n";
            cout << "1. Idle\n2. Below Normal\n3. Normal\n4. Above Normal\n5. Highest\n";
            cout << "Ваш выбор: ";
            cin >> choice;
        } while (choice < 1 || choice > 5);
        thread_priority_indices[i] = choice - 1;
    }

    vector<HANDLE> threads(size);
    all_threads.resize(size);

    for (int i = 0; i < size; ++i) {
        ThreadData* data = new ThreadData;

        int priority_index = thread_priority_indices[i];
        data->row = matrix[i];
        data->vector = vec;
        data->priority = priorities[priority_index].value;
        data->thread_id = i;
        data->completed = false;
        data->hMutex = hMutex;
        data->priority_name = priorities[priority_index].name;
        all_threads[i] = data;

        threads[i] = CreateThread(
            NULL,                   // Атрибуты безопасности по умолчанию
            0,                      // Размер стека по умолчанию
            multiply_row,           // Функция потока
            data,                   // Аргументы для функции потока
            0,                      // Флаги создания
            NULL                    // Идентификатор потока
        );
    }

    bool all_completed = false;
    while (!all_completed) {
        display_threads_status();

        all_completed = true;
        for (auto* data : all_threads) {
            if (!data->completed) {
                all_completed = false;
                break;
            }
        }

        Sleep(100);
    }

    WaitForMultipleObjects(size, threads.data(), TRUE, INFINITE);

    system("cls");
    cout << "Результат умножения матрицы на вектор:\n";
    cout << "====================================\n\n";

    for (int i = 0; i < size; ++i) {
        ThreadData* data = all_threads[i];
        cout << "Строка " << i << " (приоритет " << data->priority_name << "): "
            << data->result << endl;
    }

    for (auto* data : all_threads) {
        delete data;
    }
    for (auto thread : threads) {
        CloseHandle(thread);
    }
    CloseHandle(hMutex);

    cout << "\nНажмите любую клавишу для выхода...";
    _getch();

    return 0;
}
