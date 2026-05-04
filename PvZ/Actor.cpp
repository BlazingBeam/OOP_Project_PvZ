#include "Actor.h"

long long Actor::objects = 0;

Actor::Actor()
{
    objects++;
    cout << objects << endl;
    animateDamageColorPeakTime = 0.125;
    isAnimatingDamage = false;
    damageColor = 1;
}

void Actor::update(RenderWindow &window)
{
    cout << "Error: Actor::update(RenderWindow &window) is not implemented" << endl;
    exit(1);
}

void Actor::update(RenderWindow &window, Event &e, Cell cells[5][9])
{
    cout << "Error: Actor::update(RenderWindow &window, Event &e, Cell cells[5][9]) is not implemented" << endl;
    exit(1);
}

void Actor::update(RenderWindow &window, Cell cells[5][9])
{
    cout << "Error: Actor::update(RenderWindow &window, Cell cells[5][9]) is not implemented" << endl;
    exit(1);
}

Actor::~Actor()
{
    objects--;
    // cout << "Actor destroyed" << endl;
}

int Actor::getActorID()
{
    return actorID;
}

Img& Actor::getImg() {
    return img;
}

Coordinate& Actor::getPos() {
    return pos;
}

void Actor::setActorID(int actorID) {
    this->actorID = actorID;
}

void Actor::animateDamage(bool isAnimatingDamage, int damageType) {
    if (isAnimatingDamage) {
        animateDamageClock.restart();
        this->isAnimatingDamage = isAnimatingDamage;
    }
    if (damageType == 1) {
        damageColor = 1;
    }
    else if (damageType == 2) {
        damageColor = 2;
    }
    //smoothly change color to a red tint till peak time then back to normal after peak time
    if (this->isAnimatingDamage) {
        if (damageColor == 1){
            if (animateDamageClock.getElapsedTime().asSeconds() < animateDamageColorPeakTime) {
                img.sprite.setColor(Color(255, 255 - 255 * animateDamageClock.getElapsedTime().asSeconds() / animateDamageColorPeakTime, 255 - 255 * animateDamageClock.getElapsedTime().asSeconds() / animateDamageColorPeakTime, 255));
            }
            else if (animateDamageClock.getElapsedTime().asSeconds() < 2 * animateDamageColorPeakTime) {
                img.sprite.setColor(Color(255, 255 - 255 * (2 * animateDamageColorPeakTime - animateDamageClock.getElapsedTime().asSeconds()) / animateDamageColorPeakTime, 255 - 255 * (2 * animateDamageColorPeakTime - animateDamageClock.getElapsedTime().asSeconds()) / animateDamageColorPeakTime, 255));
            }
            else {
                img.sprite.setColor(Color(255, 255, 255, 255));
                this->isAnimatingDamage = false;
            }
        } 
        else if (damageColor == 2) {
            //same as above just blue tint instead of red
            if (animateDamageClock.getElapsedTime().asSeconds() < animateDamageColorPeakTime) {
                img.sprite.setColor(Color(255 - 255 * animateDamageClock.getElapsedTime().asSeconds() / animateDamageColorPeakTime, 255 - 255 * animateDamageClock.getElapsedTime().asSeconds() / animateDamageColorPeakTime, 255, 255));
            }
            else if (animateDamageClock.getElapsedTime().asSeconds() < 2 * animateDamageColorPeakTime) {
                img.sprite.setColor(Color(255 - 255 * (2 * animateDamageColorPeakTime - animateDamageClock.getElapsedTime().asSeconds()) / animateDamageColorPeakTime, 255 - 255 * (2 * animateDamageColorPeakTime - animateDamageClock.getElapsedTime().asSeconds()) / animateDamageColorPeakTime, 255, 255 ));
            }
            else {
                img.sprite.setColor(Color(255, 255, 255, 255));
                this->isAnimatingDamage = false;
            }
        }
    }
}

int Actor::getScoreValue()
{
    return scoreValue;
}

void Actor::setScoreValue(int scoreValue)
{
    this->scoreValue = scoreValue;
}
