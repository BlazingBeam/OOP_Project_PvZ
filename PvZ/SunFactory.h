#pragma once
#include "Vec.h"
#include "Sun.h"
#include "Cell.h"
#include <ctime>

class SunFactory {
    protected:
        int currency;

        Clock spawnClock;
        double spawnDelay;

        Vec<Sun*> sunList;
        // ActorList* actorList;
    public:
        SunFactory(int currency = 0, double spawnDelay = 10000);
        void createSun(Coordinate pos, Coordinate unitVelocity, Coordinate* target = nullptr);
        void setCurrency(int currency);
        int getCurrency();
        void addCurrency(int currency);
        void subtractCurrency(int currency);

        void update(RenderWindow& window, Cell cells[][9], Event &e);
        
        void spawnSun(Cell cells[][9]); //spawn sun at random location
        void spawnSun(Coordinate pos);  //spawn sun at pos

        void sunClicked(RenderWindow& window, Event &e);

        void collectSun();
};

