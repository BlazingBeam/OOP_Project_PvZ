#pragma once
#include "Plant.h"
#include "Attack.h"

class CherryBomb: public Plant{
    protected:
        double explosionRadius;
    public:
        CherryBomb(Coordinate pos);
        void update(RenderWindow& window);
};

