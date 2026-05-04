#pragma once
#include "Plant.h"
#include "Attack.h"
#include "Fume.h"
class FumeShroom: public Plant, public Attack{
    protected:
        
        Fume fumeList[4];
    //36x38
    public:
        FumeShroom(Coordinate pos);
        void update(RenderWindow& window);

        Fume& getFume(int i);
};

