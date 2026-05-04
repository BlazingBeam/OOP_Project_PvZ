#pragma once
#include "Zombie.h"
#include "Attack.h"
#include "BulletFactory.h"
class FootballZombie: public Zombie, public Attack
{   
    protected:
        //Attributes for switching lanes mechanism
        Clock switchClock;
        double switchCD;
        int switchState;    //0: straight, 1: switch up, -1: switch down
        int newRow;
        int currentRow;

        int &lives;
        
    public:
        FootballZombie(int &lives, Coordinate pos, BulletFactory* bulletFactory, PlantFactory* plantFactory,Cell cells[][9], double speed = 0.018);
        void update(RenderWindow& window, Cell cells[][9]);

        void switchLanes(Cell cells[][9]);
};

