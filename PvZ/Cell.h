#pragma once
#include "Coordinate.h"
#include "SFML/Graphics.hpp"
using namespace sf;
class Cell {
protected:
    bool inUse;
    bool isSunlight;
    bool canPlacePlant;
public:
    Coordinate pos;
    Cell(Coordinate pos = Coordinate());
    bool getInUse();
    bool getIsSunlight();
    void setIsSunlight(bool isSunlight);
    Coordinate& Pos();
    void setInUse(bool inUse);
    bool isMouseOver(RenderWindow &window);
    bool getCanPlacePlant();
    void setCanPlacePlant(bool canPlacePlant);
};

