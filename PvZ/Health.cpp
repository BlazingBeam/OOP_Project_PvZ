#include "Health.h"

Health::Health(double health, double armor) {
    this->health = health;
    this->armor = armor;
}

double Health::getHealth() {
    return health;
}

double Health::getArmor() {
    return armor;
}

void Health::setHealth(double health) {
    this->health = health;
}

void Health::setArmor(double armor) {
    this->armor = armor;
}

void Health::takeDamage(double damage) {
    if (armor > 0) {
        armor -= damage;
        if (armor < 0) {
            health += armor;
            armor = 0;
        }
    } else {
        health -= damage;
    }
}