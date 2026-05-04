#pragma once
#include "Coordinate.h"
#include "BulletFactory.h"
using namespace sf;
using namespace std;

class Attack {
    protected:
        BulletFactory *bulletFactory;
        // ZombieFactory *zombieFactory;
        Clock attackClock;
        double attackDelay; // in milliseconds
        double attackDamage;
    public:
        Attack(BulletFactory* bulletFactory = nullptr, double attackDelay = 3000, double attackDamage = 1);
        //Attack(ZombieFactory* zombieFactory = nullptr, double attackCD = 3000, double attackDamage = 1);
        void rangedAttack(int projectileID, Coordinate pos, Coordinate unitVelocity);
        void forceRangedAttack(int projectileID, Coordinate pos, Coordinate unitVelocity);
        void explosionAttack(int explosionID, Coordinate pos, double radius);

        void meleeAttack(int targetID);

        double getAttackDamage();
        Clock& getAttackClock();
        double getAttackDelay();
        void setAttackDelay(double attackDelay);
        void setAttackDamage(double attackDamage);
};

