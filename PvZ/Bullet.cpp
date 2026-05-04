#include "Bullet.h"

Bullet::Bullet(Coordinate pos, Coordinate unitVelocity, int id) {
    this->unitVelocity = unitVelocity;
    this->pos = pos;
    this->speed = 1;
    moveCD = 0.0025;
    attackDamage = 1;
    switch (id) {
        case 17:
        case 16: {
            img.setImg("Assets/Textures/Bullets/PeaNormal/pea.png", 28, 28);
            img.sprite.setScale(0.8, 0.8);
            actorID = 64;
            break;
        }
        case 18: {
            img.setImg("Assets/Textures/Bullets/PeaIce/icepea.png");
            actorID = 65;
            break;
        }
    }
}

void Bullet::update(RenderWindow &window) {
    move(pos);
    if (pos.x > 1080 || pos.x < 0 || pos.y > 600 || pos.y < 0) {
        actorID = -1;
    }
    // pos.display();
    img.sprite.setPosition(pos.x, pos.y + 8);
    window.draw(img.sprite);
}

double Bullet::getAttackDamage()
{
    return attackDamage;
}
