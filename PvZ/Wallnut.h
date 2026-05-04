#pragma once
#include "Plant.h"
#include "Move.h"
#include "Attack.h"
class Wallnut : public Plant, public Move, public Attack{
    protected:
        bool isRolling;
        int spriteStatus; // 3 = normal, 2 = damaged, 1 = very damaged, 0 = dead
    public:
        Wallnut(Coordinate pos);

        void update(RenderWindow& window, Event &e, Cell cells[5][9]);

        void roll(RenderWindow &window, Event &e, Cell cells[5][9]);

        bool getIsRolling();

        double getAttackDamage();

        Clock& getAttackClock();

        double getAttackDelay();
};

