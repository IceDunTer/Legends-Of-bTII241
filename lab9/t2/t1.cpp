#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// Определение класса Student
class Student
{
private:
    string name;
    int id;
public:
    // Конструктор
    Student(const string& studentName = "", int studentId = 0)
        : name(studentName), id(studentId) {}

    // Деструктор
    ~Student() {}

    // Методы для получения и установки значений
    string getName() const { return name; }
    void setName(const string& studentName) { name = studentName; }

    int getId() const { return id; }
    void setId(int studentId) { id = studentId; }

    // Метод для вывода информации о студенте
    void display() const
    {
        cout << "Name: " << name << ", ID: " << id << endl;
    }
};

// Определение шаблонного класса Array
template <typename T>
class Array
{
private:
    T* myArray;
    size_t n;
public:
    // Конструктор с параметрами
    explicit Array(size_t size = 0, const T& value = T())
        : n(size)
    {
        if (size > 0)
        {
            myArray = new T[size];
            for (size_t i = 0; i < n; ++i)
            {
                myArray[i] = value;
            }
        }
        else
        {
            myArray = nullptr;
        }
    }

    // Конструктор копирования
    Array(const Array& mas)
        : n(mas.n)
    {
        if (n > 0)
        {
            myArray = new T[n];
            for (size_t i = 0; i < n; ++i)
            {
                myArray[i] = mas.myArray[i];
            }
        }
        else
        {
            myArray = nullptr;
        }
    }

    // Деструктор
    ~Array()
    {
        delete[] myArray;
    }

    // Оператор доступа по индексу для изменения элементов
    T& operator[](size_t idx)
    {
        if (idx >= n)
        {
            throw out_of_range("Index out of range");
        }
        return myArray[idx];
    }

    // Оператор доступа по индексу для чтения элементов
    const T& operator[](size_t idx) const
    {
        if (idx >= n)
        {
            throw out_of_range("Index out of range");
        }
        return myArray[idx];
    }

    // Метод для получения размера массива
    size_t size() const
    {
        return n;
    }
};

int main()
{
    // Пример использования класса Array с типом int
    Array<int> intArray(5, 10);
    cout << "Array of ints: ";
    for (size_t i = 0; i < intArray.size(); ++i)
    {
        cout << intArray[i] << " ";
    }
    cout << endl;

    // Пример использования класса Array с типом double
    Array<double> doubleArray(5, 10.5);
    cout << "Array of doubles: ";
    for (size_t i = 0; i < doubleArray.size(); ++i)
    {
        cout << doubleArray[i] << " ";
    }
    cout << endl;

    // Пример использования класса Array с типом string
    Array<string> stringArray(5, "Hello");
    cout << "Array of strings: ";
    for (size_t i = 0; i < stringArray.size(); ++i)
    {
        cout << stringArray[i] << " ";
    }
    cout << endl;

    // Пример использования класса Array с типом char*
    Array<const char*> charPtrArray(5, "World");
    cout << "Array of char*: ";
    for (size_t i = 0; i < charPtrArray.size(); ++i)
    {
        cout << charPtrArray[i] << " ";
    }
    cout << endl;

    // Пример использования класса Array с пользовательским типом Student
    Array<Student> studentArray(3);
    studentArray[0] = Student("Artem", 1);
    studentArray[1] = Student("Anton", 2);
    studentArray[2] = Student("Kirill", 3);

    cout << "Array of Students: " << endl;
    for (size_t i = 0; i < studentArray.size(); ++i)
    {
        studentArray[i].display();
    }

    return 0;
}
