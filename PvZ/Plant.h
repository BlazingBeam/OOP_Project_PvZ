#pragma once
#include "Actor.h"
#include "BulletFactory.h"
#include "Health.h"

class Plant: public Actor, public Health{
protected:
    int cost;
public:

    virtual ~Plant() {};
    int getCost();

    Coordinate getCell(Cell cells[5][9]);

    virtual bool getIsRolling() { exit(1); return 0; };
    virtual double getAttackDamage() { exit(1); return 0; };

    virtual Clock& getAttackClock() { exit(1); return *(new Clock()); };
    virtual double getAttackDelay() { exit(1); return 0; };
};

