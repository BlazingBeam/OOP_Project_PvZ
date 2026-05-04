#pragma once
#include "Plant.h"
#include "Sunfactory.h"
class Sunflower: public Plant{
    protected:
        SunFactory* sunFactory;

        Clock sunSpawnClock;
        double sunSpawnDelay;
    public:
        Sunflower(Coordinate pos = Coordinate(), SunFactory* sunFactory = nullptr, Cell cells[][9] = nullptr);
        void update(RenderWindow& window);
};

