#pragma once
#include "Zombie.h"
// #include "MeleeAttack.h"
#include "BulletFactory.h"
class SimpleZombie: public Zombie, public Attack {
    protected:
        int &lives;
    public:
        SimpleZombie(int &lives, Coordinate pos, BulletFactory* bulletFactory, PlantFactory* plantFactory, double speed = 0.005); //slow
        void update(RenderWindow& window, Cell cells[][9]);
};

