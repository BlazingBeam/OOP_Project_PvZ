#pragma once
#include "Move.h"
#include "Actor.h"

class Sun: public Actor, public Move {
    protected:
        int value;
    public:
        Sun(int value = 50, Coordinate pos = Coordinate(), Coordinate unitVelocity = Coordinate(), Coordinate *target = nullptr);

        void update(RenderWindow& window);
        
        bool isMouseOver(RenderWindow& window);
        
        int getValue();
};

