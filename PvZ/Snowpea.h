#pragma once
#include "Plant.h"
#include "Attack.h"

class Snowpea: public Plant, public Attack {
    public:
        Snowpea(Coordinate pos, BulletFactory& bulletFactory);
        void update(RenderWindow& window);
};
