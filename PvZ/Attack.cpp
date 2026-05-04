#include "Attack.h"

Attack::Attack(BulletFactory* bulletFactory, double attackDelay, double attackDamage): bulletFactory(bulletFactory) {
    this->attackDelay = attackDelay;
    this->attackDamage = attackDamage;
    attackClock.restart();
}

void Attack::rangedAttack(int projectileID, Coordinate pos, Coordinate unitVelocity) {
    if (bulletFactory == nullptr) {
        return;
    }
    if (attackClock.getElapsedTime().asMilliseconds() > attackDelay){
        bulletFactory->createBullet(projectileID, pos, unitVelocity);
        attackClock.restart();
    }
}

void Attack::forceRangedAttack(int projectileID, Coordinate pos, Coordinate unitVelocity) {
    if (bulletFactory == nullptr) {
        return;
    }
    bulletFactory->createBullet(projectileID, pos, unitVelocity);
}

void Attack::explosionAttack(int projectileID, Coordinate pos, double explosionRadius) {
    if (attackClock.getElapsedTime().asMilliseconds() > attackDelay){
        //
    }
}

void Attack::meleeAttack(int targetID) {    //for zombies attacking plants
    //
}

double Attack::getAttackDamage()
{
    return attackDamage;
}

Clock& Attack::getAttackClock()
{
    return attackClock;
}

double Attack::getAttackDelay()
{
    return attackDelay;
}

void Attack::setAttackDelay(double attackDelay)
{
    this->attackDelay = attackDelay;
}

void Attack::setAttackDamage(double attackDamage)
{
    this->attackDamage = attackDamage;
}

