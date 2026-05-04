#pragma once
#include <iostream>
using namespace std;
class Coordinate {
public:
    float x, y;
    
    Coordinate(float xP = 0, float yP = 0);
    Coordinate(const Coordinate &c);
    void operator()(float x, float y);          //set x and y
    Coordinate& operator=(Coordinate c);             //set itself to c

    Coordinate& operator+=(Coordinate c);             //add c to itself and return itself
    Coordinate& operator-=(Coordinate c);             //subtract c from itself and return itself
    Coordinate& operator*=(float f);              //multiply itself by f and return itself
    Coordinate& operator/=(float f);              //divide itself by f and return itself
    Coordinate operator+(Coordinate c);        //return sum of itself and c
    Coordinate operator-(Coordinate c);        //return difference of itself and c
    Coordinate operator*(float f);              //return itself multiplied by f
    Coordinate operator/(float f);              //return itself divided by f
    bool operator==(Coordinate c);             //return true if itself is equal to c
    bool operator!=(Coordinate c);             //return true if itself is not equal to c
    float distance(Coordinate c);              //return distance between itself and c
    float magnitude();                          //return magnitude of itself
    Coordinate findVector(Coordinate c);    //return vector from itself to c
    Coordinate findUnitVector(Coordinate c);    //return unit vector from itself to c of MAGNIUDE 1
    void display();                            //display itself
};