#pragma once
#include "Plant.h"
#include "Attack.h"
class Repeater: public Plant, public Attack{
    protected:
        Clock doubleAttackClock;
        double doubleAttackDelay;
        bool doubleAttackReady;
    public:
        Repeater(Coordinate pos, BulletFactory& bulletFactory);
        void update(RenderWindow& window);
};

