#include<iostream>
#include<locale.h>
#include<fstream>
#include<string>
#include<list>
#include<map>

using namespace std;
void main() {
    setlocale(LC_ALL, "RUS");

    map<string, int> numbers = { };
    ifstream file("numbers.txt");
    string str1;
    int maxx = 0;

    while (file >> str1)
    {
        if (str1.length() != 11)
        {
            continue;
        }
        if (numbers[str1] > 0) {
            numbers[str1]++;
        }
        else {
            numbers[str1] = 1;
        }

        maxx = max(maxx, numbers[str1]);

    }
    cout << maxx << endl;

    for (auto pair : numbers)
    {
        if (pair.second == maxx)
        {
            cout << pair.first << endl;
        }
    }

    file.close();
}
