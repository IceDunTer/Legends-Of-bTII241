#include <iostream>
#include <cmath>
#include <locale>
using namespace std;

class Coordinate 
{
public:
	virtual ~Coordinate() {};
	virtual void printCoords() const = 0;
	virtual double getX() const = 0;
	virtual double getY() const = 0;
};

class Dekart : public Coordinate
{
private:
	double x, y;
public:
	Dekart(double x, double y) : x(x), y(y) {}

	void printCoords() const override {
		cout << "Декартовые координаты: (" << x << ", " << y << ")\n\n";
	};

	double getX() const override { return x; }
	double getY() const override { return y; }
};

class Polar : public Coordinate {
private:
	double r, a;
public:
	Polar(double r, double a) : r(r), a(a) {}

	void printCoords() const override {
		cout << "Полярные координаты: (" << r << ", " << a << ")\n\n";
	};

	double getX() const override { return r * cos(a); }
	double getY() const override { return r * sin(a); }
};

class Natural : public Coordinate {
private:
	double x, y;
public:
	Natural(double x, double y) : x(x), y(y) {}

	void printCoords() const override {
		cout << "Полярные координаты: (" << x << ", " << y << ")\n\n";
	};

	double getX() const override { return x; }
	double getY() const override { return y; }
};

Polar toPolar(const Dekart& dekart) {
	double r = sqrt(dekart.getX() * dekart.getX() +	dekart.getY() * dekart.getY());
	double a = atan2(dekart.getY(), dekart.getX());
	return Polar(r, a);
}

Dekart toDekart(const Polar& polar) {
	return Dekart(polar.getX(), polar.getY());
}

int main() {
	setlocale(LC_ALL, "RUS");
	double x, y;
	cout << "Введите декартовы координаты:" << endl;
	cin >> x >> y;

	Coordinate* dekart = new Dekart(x, y);
	Coordinate* polar = new Polar(sqrt(x * x + y * y), atan2(y, x));
	Coordinate* natural = new Natural(x, y);

	dekart->printCoords();
	polar->printCoords();

	cout << "---Декартовые в полярные:---\n";
	Polar d2p = toPolar(*dynamic_cast<Dekart*>(dekart));
	d2p.printCoords();

	cout << "---Полярные в декартовые:---\n";
	Dekart p2d = toDekart(d2p);
	p2d.printCoords();

	natural->printCoords();

	delete dekart;
	delete polar;
	delete natural;

	return 0;
}
