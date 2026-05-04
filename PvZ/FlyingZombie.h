#pragma once
#include "Zombie.h"
#include "Attack.h"
#include "BulletFactory.h"
class FlyingZombie: public Zombie, public Attack
{
    protected:
        int &lives;
    public:
        FlyingZombie(int &lives, Coordinate pos, BulletFactory* bulletFactory, double speed = 0.015);
        void update(RenderWindow& window);
};

