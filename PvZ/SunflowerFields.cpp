#include "SunflowerFields.h"
#include <iostream>
using namespace std;
using namespace sf;
SunflowerFields::SunflowerFields(int &currentLevel) : Level(currentLevel), currentLevel(currentLevel) {
    started = false;


    bg.setImg("Assets/Textures/Backgrounds/SunflowerFields.jpg"); //1400x600
    bg.sprite.setScale(2, 2);  
    bg.sprite.setOrigin(145, 60);
    pos += Coordinate(-320, 0);
    animateVector = pos.findUnitVector(Coordinate(0, 0));
    isAnimating = false;

    mode = -1;
    sunFactory.setCurrency(200);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            //each cell is 80x100 starting at 264, 100
            cells[i][j].pos = Coordinate(264 + j * 80, 100 + i * 95);
            //set cells in last 4 columns to not be able to place plants
            if (j >= 5) {
                cells[i][j].setCanPlacePlant(false);
            }
            //randomly set 6 cells of the first 2 columns to be sunlight
            if (j < 2) {
                if (rand() % 2 == 0) {
                    cells[i][j].setIsSunlight(true);
                    sunlightCellCount++;
                }
            }
        }
    }
}

void SunflowerFields::doAnimate() {
    if (animateClock.getElapsedTime().asSeconds() > 0.001) {
        pos += animateVector;
        animateClock.restart();
        if (pos == Coordinate(0, 0)) {
            isAnimating = -1;
            mode = 0;
        }
    }
}

void SunflowerFields::update(RenderWindow& window, Event &e, int modeP) {
    if (zombieFactory.getZombieSpawnDelay() > 5) zombieFactory.setZombieSpawnDelay(zombieFactory.getZombieSpawnDelay() - 0.0000001);
    if (!started) animateClock.restart();
    started = true;
    if (animateClock.getElapsedTime().asSeconds() > 3 && isAnimating == 0) {    //isAnimating == 0 means not animated yet, isAnimating == 1 means animating, isAnimating == -1 means done animating
        animateClock.restart();
        isAnimating = 1;
    }
    if (isAnimating == 1) {
        doAnimate();
    }
    //draw transparent white circle over sunlight cells
    Level::update(window, e);
}


int SunflowerFields::getZombieCount() {
    return zombieFactory.getZombieCount();
}

int SunflowerFields::getTotalZombies() {
    return zombieFactory.getTotalZombies();
}

int SunflowerFields::getZombiesKilled() {
    return zombieFactory.getZombiesKilled();
}