#include "Coordinate.h"
#include <cmath>
using namespace std;

Coordinate::Coordinate(float xP, float yP) : x(xP), y(yP) {}

Coordinate::Coordinate(const Coordinate &c) : x(c.x), y(c.y) {}

void Coordinate::operator()(float x, float y) { this->x = x; this->y = y; }

Coordinate& Coordinate::operator=(Coordinate c) { x = c.x; y = c.y; return *this; }

Coordinate& Coordinate::operator+=(Coordinate c) { x += c.x; y += c.y; return *this; }

Coordinate& Coordinate::operator-=(Coordinate c) { x -= c.x; y -= c.y; return *this; }

Coordinate& Coordinate::operator*=(float f) { x *= f; y *= f; return *this; }

Coordinate& Coordinate::operator/=(float f) { x /= f; y /= f; return *this; }

Coordinate Coordinate::operator+(Coordinate c) { return Coordinate(x + c.x, y + c.y); }

Coordinate Coordinate::operator-(Coordinate c) { return Coordinate(x - c.x, y - c.y); }

Coordinate Coordinate::operator*(float f) { return Coordinate(x * f, y * f); }

Coordinate Coordinate::operator/(float f) { return Coordinate(x / f, y / f); }
bool Coordinate::operator==(Coordinate c) { return x == c.x && y == c.y; }

bool Coordinate::operator!=(Coordinate c) { return x != c.x || y != c.y; }

float Coordinate::distance(Coordinate c) { return sqrt(pow(x - c.x, 2) + pow(y - c.y, 2)); }

float Coordinate::magnitude() { return sqrt(pow(x, 2) + pow(y, 2)); }

Coordinate Coordinate::findVector(Coordinate c) { return Coordinate(c.x - x, c.y - y); }

Coordinate Coordinate::findUnitVector(Coordinate c) {
    Coordinate v = findVector(c);
    return v / v.magnitude();
}

void Coordinate::display() {
    cout << "(" << x << ", " << y << ")" << endl;
}