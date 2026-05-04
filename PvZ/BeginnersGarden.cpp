#include "BeginnersGarden.h"
#include <iostream>
using namespace std;
using namespace sf;
BeginnersGarden::BeginnersGarden(int &currentLevel) : Level(currentLevel), currentLevel(currentLevel), lawnMowers{LawnMower(0, cells), LawnMower(1, cells), LawnMower(2, cells), LawnMower(3, cells), LawnMower(4, cells)} {
    started = false;

    zombieFactory.setLawnMowers(lawnMowers);


    bg.setImg("Assets/Textures/Backgrounds/bgday.jpg"); //1400x600
    pos += Coordinate(-320, 0);
    animateVector = pos.findUnitVector(Coordinate(0, 0));
    isAnimating = false;

    mode = -1;
    sunFactory.setCurrency(0);
    //use all lawnmowers (Debug)
}

void BeginnersGarden::doAnimate() {
    if (animateClock.getElapsedTime().asSeconds() > 0.001) {
        pos += animateVector;
        animateClock.restart();
        if (pos == Coordinate(0, 0)) {
            isAnimating = -1;
            mode = 0;
        }
    }
}

void BeginnersGarden::update(RenderWindow& window, Event &e, int modeP) {
    if (!started) animateClock.restart();
    started = true;
    if (animateClock.getElapsedTime().asSeconds() > 3 && isAnimating == 0) {    //isAnimating == 0 means not animated yet, isAnimating == 1 means animating, isAnimating == -1 means done animating
        animateClock.restart();
        isAnimating = 1;
    }
    if (isAnimating == 1) {
        doAnimate();
    }
    Level::update(window, e);
    if (mode == 0) {
        for (int i = 0; i < 5; i++) {
            lawnMowers[i].update(window);
        }
    }
}


int BeginnersGarden::getZombieCount() {
    return zombieFactory.getZombieCount();
}

int BeginnersGarden::getTotalZombies() {
    return zombieFactory.getTotalZombies();
}

int BeginnersGarden::getZombiesKilled() {
    return zombieFactory.getZombiesKilled();
}