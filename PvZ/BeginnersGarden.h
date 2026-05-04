#pragma once
#include "Level.h"
#include "LawnMower.h"

class BeginnersGarden : public Level {
    protected:
        bool started;

        int isAnimating;
        Clock animateClock;
        Coordinate animateVector;

        int mode;
        int &currentLevel;

        LawnMower lawnMowers[5];

    public:
        BeginnersGarden(int &currentLevel);
        void doAnimate();   //animation sequence
        void update(RenderWindow& window, Event &e, int modeP = 0);    //mode: 0: draw everything, -1: only bg

        int getZombieCount();
        int getTotalZombies();
        int getZombiesKilled();
};