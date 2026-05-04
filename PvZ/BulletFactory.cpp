#include "BulletFactory.h"

BulletFactory::BulletFactory() {}

BulletFactory::~BulletFactory() {
    for (int i = 0; i < bulletList.length(); i++) {
        bulletList[i]->setActorID(-1);
    }
    bulletList.clear();
}

void BulletFactory::createBullet(int plantID, Coordinate pos, Coordinate unitVelocity) {
    Bullet *bullet = nullptr;
    if (plantID >= 16 && plantID <= 21) bullet = new Bullet(pos, unitVelocity, plantID);
    if (bullet) {
        bulletList.push(bullet);
    }
}

void BulletFactory::update(RenderWindow &window) {
    for (int i = 0; i < bulletList.length(); i++) {
        bulletList[i]->update(window);
    }
    bulletCleanup();
}

void BulletFactory::bulletCleanup() {
    for (int i = 0; i < bulletList.length(); i++) {
        if (bulletList[i]->getActorID() == -1) {
            delete bulletList[i];   //composition
            bulletList.popAt(i);
            i--;
        }
    }
}

Vec<Bullet*> &BulletFactory::getBulletList() {
    return bulletList;
}
