#include "Cell.h"
#include "SFML/Graphics.hpp"
using namespace sf;

Cell::Cell(Coordinate pos): pos(pos), inUse(false), isSunlight(false), canPlacePlant(true) {};

bool Cell::getInUse() { return inUse; }

bool Cell::getIsSunlight()
{
    return isSunlight;
}

void Cell::setIsSunlight(bool isSunlight)
{
    this->isSunlight = isSunlight;
}

Coordinate& Cell::Pos() { return pos; }

void Cell::setInUse(bool inUse) { this->inUse = inUse; }

bool Cell::isMouseOver(RenderWindow &window) {
    double mousePosX = Mouse::getPosition(window).x;
    double mousePosY = Mouse::getPosition(window).y;
    //each cell in the grid is 80x95
    return (mousePosX >= pos.x && mousePosX <= pos.x + 80 && mousePosY >= pos.y && mousePosY <= pos.y + 95);
}

bool Cell::getCanPlacePlant()
{
    return canPlacePlant;
}

void Cell::setCanPlacePlant(bool canPlacePlant)
{
    this->canPlacePlant = canPlacePlant;
}