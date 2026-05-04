#pragma once
#include "Img.h"
#include "Attack.h"
class Fume: public Actor, public Attack {
    protected:
        Clock lifetimeClock;
        double lifetime;    //in seconds

        bool isActive;
    public:
        Fume(Coordinate pos);
        void update(RenderWindow& window);
        void setLifetime(double lifetime);
        double getLifetime();

        void setActive(bool isActive);

        bool getIsActive();

        void setIsActive(bool isActive);

};
