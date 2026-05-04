#include "Plant.h"

int Plant::getCost()
{
    return cost;
}

Coordinate Plant::getCell(Cell cells[5][9]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (cells[i][j].pos.x == pos.x && cells[i][j].pos.y == pos.y) {
                return Coordinate(j, i);
            }
        }
    }
}