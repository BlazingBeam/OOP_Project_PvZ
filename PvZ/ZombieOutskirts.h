#pragma once
#include "Level.h"

class ZombieOutskirts : public Level {
    protected:
        bool started;

        int isAnimating;
        Clock animateClock;
        Coordinate animateVector;

        int mode;
        int &currentLevel;

    public:
        ZombieOutskirts(int &currentLevel);
        void doAnimate();   //animation sequence
        void update(RenderWindow& window, Event &e, int modeP = 0);

        int getZombieCount();
        int getTotalZombies();
        int getZombiesKilled();
};