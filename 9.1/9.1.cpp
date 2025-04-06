#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

struct PhoneNumber {
    string number;
    int count;
};

int main()
{
    setlocale(LC_ALL, "Rus");

    smatch result;
    regex numreg(R"(\+?\d+[\s-]([\d]{3}|\([\d]{3}\))[\s-][\d]{3}[\s-]([\d]{4}|[\d]{2}[\s-][\d]{2}))");
    string line, file = "History1.txt";

    vector<PhoneNumber> frequency;  // ������������ ������ ��� �������� ������� � �� �������
    int max_count = 0;
    string most_frequent_number;

    ifstream in(file);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            if (regex_search(line, result, numreg))
            {
                string number = result[0];
                bool found = false;

                for (auto& phone : frequency) {
                    if (phone.number == number) {
                        phone.count++;  // ����������� ������� ��� ������������� ������
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    frequency.push_back(PhoneNumber{ number, 1 });  // ��������� ����� ����� � ��������� ���������
                }

                cout << number << endl;
            }
        }
        in.close();
    }
    else
    {
        cout << "������ �������� �����!" << endl;
        return 1;
    }

    // ���� ����� � ���������� ��������
    for (const auto& phone : frequency)
    {
        if (phone.count > max_count) {
            max_count = phone.count;
            most_frequent_number = phone.number;
        }
    }

    cout << "����� �������� � ����� ������� ����������� �������: " << endl;
    cout << most_frequent_number << " (����������: " << max_count << ")" << endl;
    return 0;
}
