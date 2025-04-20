#include <windows.h>
#include <vector>
#include <string>
#include <commctrl.h>
#include <sstream>
#include <iomanip>
#include <algorithm>

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace std;

// Идентификаторы элементов управления
#define IDC_SIZE_EDIT 101
#define IDC_MATRIX_EDIT 102
#define IDC_VECTOR_EDIT 103
#define IDC_START_BUTTON 104
#define IDC_RESULT_LIST 105
#define IDC_THREAD_PRIORITY_BASE 200
#define IDC_SET_PRIORITIES_BUTTON 106

// Структура для данных потока
struct ThreadData {
    vector<int> row;
    vector<int> vector;
    int priority;
    int thread_id;
    int result;
    bool completed;
    int progress;
    string priority_name;
};

// Глобальные переменные
vector<ThreadData*> all_threads;
vector<HWND> hProgressBars;
vector<HWND> hPriorityCombos;
HWND hMainWnd, hStatusWnd, hResultList;
HWND hMatrixEdit, hVectorEdit, hSizeEdit, hStartButton, hSetPrioritiesButton;
int matrixSize = 3;
bool calculationInProgress = false;
bool prioritiesSet = false;

// Функции для работы с данными
vector<int> ParseNumbers(const wstring& text) {
    vector<int> numbers;
    wstringstream ws(text);
    int num;
    while (ws >> num) {
        numbers.push_back(num);
    }
    return numbers;
}

vector<vector<int>> ParseMatrix(const wstring& text, int size) {
    vector<vector<int>> matrix;
    wstringstream ws(text);
    wstring line;

    while (getline(ws, line)) {
        vector<int> row = ParseNumbers(line);
        if (row.size() == size) {
            matrix.push_back(row);
            if (matrix.size() == size) break;
        }
    }

    return matrix;
}

// Функция потока для умножения
DWORD WINAPI MultiplyRow(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    data->result = 0;

    for (size_t i = 0; i < data->row.size(); ++i) {
        data->result += data->row[i] * data->vector[i];
        data->progress = (i + 1) * 100 / data->row.size();

        PostMessage(hMainWnd, WM_APP + 1, data->thread_id, data->progress);
        Sleep(100 + (100 - data->priority * 20)); // Задержка зависит от приоритета
    }

    data->completed = true;
    PostMessage(hMainWnd, WM_APP + 2, data->thread_id, data->result);
    return 0;
}

// Создание элементов интерфейса
void CreateControls(HWND hwnd) {
    // Поля ввода
    CreateWindowW(L"STATIC", L"Размер матрицы",
        WS_VISIBLE | WS_CHILD, 20, 20, 150, 20, hwnd, NULL, NULL, NULL);

    hSizeEdit = CreateWindowW(L"EDIT", L"3",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
        180, 20, 50, 20, hwnd, (HMENU)IDC_SIZE_EDIT, NULL, NULL);

    CreateWindowW(L"BUTTON", L"Приоритет",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        240, 20, 100, 20, hwnd, (HMENU)IDC_SET_PRIORITIES_BUTTON, NULL, NULL);

    CreateWindowW(L"STATIC", L"Матрица (по строкам):",
        WS_VISIBLE | WS_CHILD, 20, 50, 300, 20, hwnd, NULL, NULL, NULL);

    hMatrixEdit = CreateWindowW(L"EDIT", L"1 2 3\n4 5 6\n7 8 9",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
        20, 70, 300, 100, hwnd, (HMENU)IDC_MATRIX_EDIT, NULL, NULL);

    CreateWindowW(L"STATIC", L"Вектор:",
        WS_VISIBLE | WS_CHILD, 20, 180, 300, 20, hwnd, NULL, NULL, NULL);

    hVectorEdit = CreateWindowW(L"EDIT", L"1 2 3",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        20, 200, 300, 20, hwnd, (HMENU)IDC_VECTOR_EDIT, NULL, NULL);

    // Кнопка запуска
    hStartButton = CreateWindowW(L"BUTTON", L"Вычислить",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        20, 230, 100, 30, hwnd, (HMENU)IDC_START_BUTTON, NULL, NULL);
    EnableWindow(hStartButton, FALSE);

    // Список результатов
    hResultList = CreateWindowW(L"LISTBOX", NULL,
        WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
        350, 20, 300, 200, hwnd, (HMENU)IDC_RESULT_LIST, NULL, NULL);

    // Статусная строка
    hStatusWnd = CreateWindowW(L"STATIC", L"Приоритет",
        WS_VISIBLE | WS_CHILD | SS_LEFT,
        20, 400, 650, 20, hwnd, NULL, NULL, NULL);
}

// Создание элементов для выбора приоритетов
void CreatePriorityControls(HWND hwnd, int count) {
    // Очищаем предыдущие элементы
    for (auto hwnd : hPriorityCombos) DestroyWindow(hwnd);
    hPriorityCombos.clear();

    // Создаем новые элементы
    for (int i = 0; i < count; i++) {
        // Подпись
        wstring label = L"Поток " + to_wstring(i) + L":";
        CreateWindowW(L"STATIC", label.c_str(),
            WS_VISIBLE | WS_CHILD,
            20, 280 + i * 30, 60, 20, hwnd, NULL, NULL, NULL);

        // Комбобокс для приоритета
        HWND hCombo = CreateWindowW(L"COMBOBOX", NULL,
            WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
            90, 280 + i * 30, 150, 120, hwnd, (HMENU)(IDC_THREAD_PRIORITY_BASE + i), NULL, NULL);

        // Заполняем приоритеты
        const wchar_t* priorities[] = { L"Idle", L"Low", L"Normal", L"High", L"Highest" };
        for (int j = 0; j < 5; j++) {
            SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)priorities[j]);
        }
        SendMessageW(hCombo, CB_SETCURSEL, 2, 0); // По умолчанию Normal
        hPriorityCombos.push_back(hCombo);
    }

    prioritiesSet = true;
    EnableWindow(hStartButton, TRUE);
}

// Создание элементов для отображения прогресса
void CreateProgressControls(HWND hwnd, int count) {
    // Очищаем предыдущие элементы
    for (auto hwnd : hProgressBars) DestroyWindow(hwnd);
    hProgressBars.clear();

    // Создаем новые элементы
    for (int i = 0; i < count; i++) {
        // Прогресс-бар
        HWND hProgress = CreateWindowW(PROGRESS_CLASS, NULL,
            WS_VISIBLE | WS_CHILD | PBS_SMOOTH,
            350, 230 + i * 30, 200, 20, hwnd, NULL, NULL, NULL);
        SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
        SendMessage(hProgress, PBM_SETSTEP, 1, 0);
        hProgressBars.push_back(hProgress);
    }
}

// Получение приоритета потока из выбранного значения комбобокса
int GetPriorityFromCombo(HWND hCombo) {
    int priorities[] = {
        THREAD_PRIORITY_IDLE,
        THREAD_PRIORITY_BELOW_NORMAL,
        THREAD_PRIORITY_NORMAL,
        THREAD_PRIORITY_ABOVE_NORMAL,
        THREAD_PRIORITY_HIGHEST
    };

    int selected = (int)SendMessageW(hCombo, CB_GETCURSEL, 0, 0);
    if (selected >= 0 && selected < 5) {
        return priorities[selected];
    }
    return THREAD_PRIORITY_NORMAL;
}

// Получение имени приоритета
wstring GetPriorityName(int priority) {
    switch (priority) {
    case THREAD_PRIORITY_IDLE: return L"Idle";
    case THREAD_PRIORITY_BELOW_NORMAL: return L"Low";
    case THREAD_PRIORITY_NORMAL: return L"Normal";
    case THREAD_PRIORITY_ABOVE_NORMAL: return L"High";
    case THREAD_PRIORITY_HIGHEST: return L"Highest";
    default: return L"Normal";
    }
}

// Запуск вычислений
void StartCalculation(HWND hwnd) {
    if (calculationInProgress || !prioritiesSet) return;

    // Получаем данные матрицы и вектора
    wchar_t matrixBuffer[1000], vectorBuffer[100];
    GetWindowTextW(hMatrixEdit, matrixBuffer, 1000);
    GetWindowTextW(hVectorEdit, vectorBuffer, 100);

    vector<vector<int>> matrix = ParseMatrix(matrixBuffer, matrixSize);
    vector<int> vec = ParseNumbers(vectorBuffer);

    // Проверка данных
    if (matrix.size() != matrixSize || vec.size() != matrixSize) {
        MessageBoxW(hwnd, L"Неверный формат данных! Проверьте размеры.", L"Ошибка", MB_ICONERROR);
        return;
    }

    // Очищаем предыдущие результаты
    SendMessageW(hResultList, LB_RESETCONTENT, 0, 0);

    // Создаем элементы для отображения прогресса
    CreateProgressControls(hwnd, matrixSize);

    // Очищаем предыдущие потоки
    for (auto* data : all_threads) delete data;
    all_threads.clear();

    // Создаем потоки
    vector<HANDLE> threads(matrixSize);
    all_threads.resize(matrixSize);
    calculationInProgress = true;

    for (int i = 0; i < matrixSize; i++) {
        ThreadData* data = new ThreadData;
        data->row = matrix[i];
        data->vector = vec;
        data->thread_id = i;
        data->completed = false;
        data->progress = 0;

        // Получаем выбранный приоритет
        data->priority = GetPriorityFromCombo(hPriorityCombos[i]);
        data->priority_name = string(GetPriorityName(data->priority).begin(), GetPriorityName(data->priority).end());

        all_threads[i] = data;
        threads[i] = CreateThread(NULL, 0, MultiplyRow, data, 0, NULL);
        SetThreadPriority(threads[i], data->priority);
    }

    SetWindowTextW(hStatusWnd, L"Вычисление...");
    EnableWindow(hStartButton, FALSE);
}

// Оконная процедура
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateControls(hwnd);
        break;

    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {
            if (LOWORD(wParam) == IDC_START_BUTTON) {
                StartCalculation(hwnd);
            }
            else if (LOWORD(wParam) == IDC_SET_PRIORITIES_BUTTON) {
                // Получаем размер матрицы
                wchar_t sizeText[10];
                GetWindowTextW(hSizeEdit, sizeText, 10);
                matrixSize = max(2, min(10, _wtoi(sizeText)));

                // Создаем элементы для выбора приоритетов
                CreatePriorityControls(hwnd, matrixSize);
                SetWindowTextW(hStatusWnd, L"Установите приоритеты потоков и нажмите 'Вычислить'");
            }
        }
        break;

    case WM_APP + 1: // Обновление прогресса
        if (wParam < hProgressBars.size()) {
            SendMessage(hProgressBars[wParam], PBM_SETPOS, lParam, 0);

            wstringstream ws;
            ws << L"Поток " << wParam << L": " << lParam << L"% ("
                << GetPriorityName(all_threads[wParam]->priority) << L")";

            if (SendMessageW(hResultList, LB_GETCOUNT, 0, 0) > wParam) {
                SendMessageW(hResultList, LB_DELETESTRING, wParam, 0);
            }
            SendMessageW(hResultList, LB_INSERTSTRING, wParam, (LPARAM)ws.str().c_str());
        }
        break;

    case WM_APP + 2: // Завершение потока
        if (wParam < hProgressBars.size()) {
            wstringstream ws;
            ws << L"Поток " << wParam << L" (" << GetPriorityName(all_threads[wParam]->priority)
                << L") завершен. Результат: " << lParam;

            SendMessageW(hResultList, LB_DELETESTRING, wParam, 0);
            SendMessageW(hResultList, LB_INSERTSTRING, wParam, (LPARAM)ws.str().c_str());

            // Проверяем завершение всех потоков
            bool allCompleted = true;
            for (auto* data : all_threads) {
                if (!data->completed) {
                    allCompleted = false;
                    break;
                }
            }

            if (allCompleted) {
                SetWindowTextW(hStatusWnd, L"Все вычисления завершены!");
                EnableWindow(hStartButton, TRUE);
                calculationInProgress = false;
            }
        }
        break;

    case WM_DESTROY:
        for (auto* data : all_threads) delete data;
        all_threads.clear();
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Точка входа
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Инициализация элементов управления
    INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX), ICC_PROGRESS_CLASS };
    InitCommonControlsEx(&icc);

    // Регистрация класса окна
    WNDCLASSEXW wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0,
                      hInstance, NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1),
                      NULL, L"MatrixMultiplierClass", NULL };

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(NULL, L"Ошибка регистрации окна!", L"Ошибка", MB_ICONERROR);
        return 0;
    }

    // Создание главного окна
    hMainWnd = CreateWindowW(L"MatrixMultiplierClass", L"Умножение матрицы на вектор",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        700, 450, NULL, NULL, hInstance, NULL);

    if (!hMainWnd) {
        MessageBoxW(NULL, L"Ошибка создания окна!", L"Ошибка", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    // Цикл сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
