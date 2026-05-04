#pragma once
#include "Move.h"
#include "Img.h"
#include "Actor.h"
// #include "MeleeAttack.h"

class Bullet : public Actor, public Move {
    protected:
        double attackDamage;
    public:
        Bullet(Coordinate pos = Coordinate(), Coordinate unitVelocity = Coordinate(), int id = 16);
        virtual ~Bullet() {};
        void update(RenderWindow &window);

        double getAttackDamage();
};

