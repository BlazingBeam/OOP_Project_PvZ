#include "ZombieOutskirts.h"
#include <iostream>
using namespace std;
using namespace sf;
ZombieOutskirts::ZombieOutskirts(int &currentLevel) : Level(currentLevel), currentLevel(currentLevel) {
    started = false;


    bg.setImg("Assets/Textures/Backgrounds/ZombieOutskirts.jpg"); //1400x600
    bg.sprite.setScale(2, 2);  
    bg.sprite.setOrigin(145, 60);
    pos += Coordinate(-320, 0);
    animateVector = pos.findUnitVector(Coordinate(0, 0));
    isAnimating = false;

    mode = -1;
    sunFactory.setCurrency(300);


    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            //each cell is 80x100 starting at 264, 100
            cells[i][j].pos = Coordinate(264 + j * 80, 100 + i * 95);
            cells[i][j].setInUse(false);
        }
    }
}

void ZombieOutskirts::doAnimate() {
    if (animateClock.getElapsedTime().asSeconds() > 0.001) {
        pos += animateVector;
        animateClock.restart();
        if (pos == Coordinate(0, 0)) {
            isAnimating = -1;
            mode = 0;
        }
    }
}

void ZombieOutskirts::update(RenderWindow& window, Event &e, int modeP) {
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
}


int ZombieOutskirts::getZombieCount() {
    return zombieFactory.getZombieCount();
}

int ZombieOutskirts::getTotalZombies() {
    return zombieFactory.getTotalZombies();
}

int ZombieOutskirts::getZombiesKilled() {
    return zombieFactory.getZombiesKilled();
}