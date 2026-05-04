#pragma once
#include "SFML/Graphics.hpp"
#include "Coordinate.h"
using namespace sf;

class Move {
    protected:
        Clock moveClock;
        double moveCD;
        Coordinate unitVelocity;
        double speed;

        Coordinate* target;

        Clock slowClock;
        double slowDuration;
        double slowFactor;
        bool isSlowed;

        double originalSpeed;
    public:
        Move(Coordinate unitVelocity = Coordinate(), Coordinate* target = nullptr);
        void move(Coordinate &pos);

        void setSpeed(double speed);
        void setUnitVelocity(Coordinate unitVelocity);

        double getSpeed();

        void setTarget(Coordinate* target = nullptr, Coordinate pos = Coordinate());

        void slowDown(double slowFactor = 0, double slowDuration = 0, bool isSlowed = false);
};