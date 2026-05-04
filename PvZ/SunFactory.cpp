#include "SunFactory.h"

SunFactory::SunFactory(int currency, double spawnDelay) {
    this->currency = currency;
    this->spawnDelay = spawnDelay;
}

void SunFactory::createSun(Coordinate pos, Coordinate unitVelocity, Coordinate* target) {
    Sun* sun = new Sun(50, pos, unitVelocity, target);
    sunList.push(sun);
}

void SunFactory::setCurrency(int currency) {
    this->currency = currency;
}

int SunFactory::getCurrency() {
    return currency;
}

void SunFactory::addCurrency(int currency) {
    this->currency += currency;
}

void SunFactory::subtractCurrency(int currency) {
    this->currency -= currency;
}

void SunFactory::update(RenderWindow &window, Cell cells[][9], Event &e)
{
    spawnSun(cells);
    sunClicked(window, e);
    collectSun();
    for (int i = 0; i < sunList.length(); i++) {
        sunList[i]->update(window);
    }
}

void SunFactory::spawnSun(Cell cells[][9]){
    if (spawnClock.getElapsedTime().asMilliseconds() > spawnDelay){
        double xStart = cells[0][0].pos.x;
        double xEnd = cells[4][8].pos.x + (cells[4][8].pos.x - cells[3][8].pos.x);

        double yStart = cells[0][0].pos.y;
        double yEnd = cells[4][8].pos.y + (cells[4][8].pos.y - cells[3][8].pos.y);

        double xRand = xStart + rand()%int(xEnd - xStart);
        double yRand = yStart + rand()%int(yEnd - yStart);


        Coordinate target(xRand, yRand);
        Coordinate spawnLoc(xRand, -50);
        Coordinate unitVelocity = spawnLoc.findUnitVector(target);
        // unitVelocity.display();
        createSun(spawnLoc, unitVelocity, new Coordinate(target));
        spawnClock.restart();
    }
}

void SunFactory::spawnSun(Coordinate pos) {
    createSun(pos, Coordinate(0, 0));
}

void SunFactory::sunClicked(RenderWindow& window, Event &e) {
    if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left){
        for (int i = 0; i < sunList.length(); i++) {
            if (sunList[i]->isMouseOver(window)) {
                sunList[i]->setTarget(new Coordinate(0, 0), sunList[i]->getPos());
                sunList[i]->setSpeed(1);
            }
        }
    }
}

void SunFactory::collectSun() {
    for (int i = 0; i < sunList.length(); i++) {
        if (sunList[i]->getSpeed() == 0 && sunList[i]->getPos().distance(Coordinate(0, 0)) < 3) {
            addCurrency(sunList[i]->getValue());
            sunList[i]->setActorID(-1);
            delete sunList[i];
            sunList.popAt(i);
        }
    }
}