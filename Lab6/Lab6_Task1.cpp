#include <iostream>
#include <cmath>
#include <locale>
using namespace std;

class Dot {
protected:
    double x, y;

public:
    Dot() : x(0), y(0) {}
    Dot(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

    void setCoordinates(double xCoord, double yCoord) {
        x = xCoord;
        y = yCoord;
    }

    void getCoords(double& xCoord, double& yCoord) const {
        xCoord = x;
        yCoord = y;
    }

    void display() const {
        cout << "Координаты точки: (" << x << ", " << y << ")" << endl;
    }
};

class Square : public Dot {
private:
    double side;

public:
    Square() : Dot(), side(0) {}
    Square(double xCoord, double yCoord, double s) : Dot(xCoord, yCoord), side(s) {}

    void setSide(double s) {
        side = s;
    }

    double getSide() const {
        return side;
    }

    double area() const {
        return side * side;
    }

    double perimeter() const {
        return 4 * side;
    }

    void display() const {
        Dot::display();
        cout << "Длина стороны квадрата: " << side << endl;
        cout << "Площадь: " << area() << endl;
        cout << "Периметр: " << perimeter() << endl;
    }
};

class Cube : public Square {
public:
    Cube() : Square() {}
    Cube(double xCoord, double yCoord, double s) : Square(xCoord, yCoord, s) {}

    double volume() const {
        return pow(getSide(), 3);
    }

    void display() const {
        Square::display();
        cout << "Объем куба: " << volume() << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    int x, y, a;
    cout << "Введите координаты точки:" << endl;
    cin >> x;
    cin >> y;
    cout << "Введите длину стороны квадрата:" << endl;
    cin >> a;
    Cube Cube(x, y, a);
    Cube.display();
    return 0;
}
