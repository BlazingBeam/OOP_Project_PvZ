#pragma once
#include "Level.h"

class SunflowerFields : public Level {
    protected:
        bool started;

        int isAnimating;
        Clock animateClock;
        Coordinate animateVector;

        int mode;
        int &currentLevel;

        int sunlightCellCount;

    public:
        SunflowerFields(int &currentLevel);
        void doAnimate();   //animation sequence
        void update(RenderWindow& window, Event &e, int modeP = 0);

        int getZombieCount();
        int getTotalZombies();
        int getZombiesKilled();
};