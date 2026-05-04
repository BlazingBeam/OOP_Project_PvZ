#pragma once
#include "Plant.h"
#include "Attack.h"
#include "BulletFactory.h"
using namespace std;

class Peashooter : public Plant, public Attack {
public:
    Peashooter(Coordinate pos, BulletFactory& bulletFactory);
    void update(RenderWindow& window);
};

