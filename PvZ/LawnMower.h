#pragma once
#include "Move.h"
#include "Attack.h"
#include "Actor.h"
class LawnMower: public Actor, public Move, public Attack {
    protected:
        bool isActive;
    public:
        LawnMower(int row, Cell cells[5][9]);
        void update(RenderWindow& window);

        void use();
        bool getIsActive();
};

