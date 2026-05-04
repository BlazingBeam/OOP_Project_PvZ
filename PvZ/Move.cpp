#include "Move.h"

Move::Move(Coordinate unitVelocity, Coordinate* target) {
    this->unitVelocity = unitVelocity;
    if (target) {
        this->target = target;
    }
}

void Move::move(Coordinate &pos) {
    slowDown();
    if (target){
        //cout << "Pos: "; pos.display();
        //cout << "Target: "; target->display();
        double distance = pos.distance(*target);
        if (distance <= 3) {
            speed = 0;
        }
    }
    if (moveClock.getElapsedTime().asSeconds() > moveCD) {
        pos.x += unitVelocity.x*speed;
        pos.y += unitVelocity.y*speed;
        moveClock.restart();
    }
}

void Move::setSpeed(double speed) {
    this->speed = speed;
}

void Move::setUnitVelocity(Coordinate unitVelocity) {
    this->unitVelocity = unitVelocity;
}

double Move::getSpeed() {
    return speed;
}

void Move::setTarget(Coordinate* target, Coordinate pos) {
    delete this->target;
    this->target = target;
    if (target){
        unitVelocity = pos.findUnitVector(*target);
    }
}

void Move::slowDown(double slowFactor, double slowDuration, bool isSlowed) {
    if (isSlowed) {
        if (!this->isSlowed) {
            this->slowFactor = slowFactor;
            this->slowDuration = slowDuration;
            originalSpeed = speed;
            speed = speed * slowFactor;
            slowClock.restart();
        }
        this->isSlowed = isSlowed;
    }
    if (this->isSlowed) {
        // cout << "Clock: " << slowClock.getElapsedTime().asSeconds() << endl;
        // cout << "Limit: " << this->slowDuration << endl;
        if (slowClock.getElapsedTime().asSeconds() > this->slowDuration) {
            speed = originalSpeed;
            this->isSlowed = false;
            // cout << "Speed: " << speed << endl;
        }
    }
}