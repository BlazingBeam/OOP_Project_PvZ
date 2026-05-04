#pragma once
#include "Zombie.h"
#include "Attack.h"
#include "BulletFactory.h"
#include "SimpleZombie.h"

class DancingZombie: public Zombie, public Attack
{
    protected:
        Vec<Zombie*>* zombies;
        BulletFactory* bulletFactory;
        PlantFactory* plantFactory;

        Clock spawnClock;
        double spawnDelay;  //in seconds

        int currentRow;
        Clock switchClock;
        double switchCD;    //in seconds
        int switchState;
        int newRow;

        int &lives;
    public:
        DancingZombie(int &lives, Coordinate pos, Vec<Zombie*> *zombies, BulletFactory* bulletFactory, PlantFactory* plantFactory, Cell cells[][9], double speed = 0.028);

        void update(RenderWindow& window, Cell cells[][9]);
        void spawnZombie(Cell cells[][9], BulletFactory *bulletFactory, PlantFactory *plantFactory);

        void switchLanes(Cell cells[][9]);
};

