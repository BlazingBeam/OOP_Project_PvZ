#include "FumeShroom.h"

FumeShroom::FumeShroom(Coordinate pos): fumeList{Fume(pos + Coordinate(80, 0)), Fume(pos + Coordinate(2*80, 0)), Fume(pos + Coordinate(3*80, 0)), Fume(pos + Coordinate(4*80, 0))}
{
    img.setImg("Assets/Textures/Plants/PuffShroom/PuffShroom/spritesheet.png", 40, 66);
    img.setFrames(14, 75);
    this->pos = pos;
    this->health = 4;
    this->cost = 75;

    this->actorID = 22;

    attackDelay = 1500;
}

void FumeShroom::update(RenderWindow& window)
{
    animateDamage();
    img.updateAnimation();
    img.sprite.setPosition(pos.x, pos.y);
    if (attackClock.getElapsedTime().asMilliseconds() > attackDelay)
    {
        for (int i = 0; i < 4; i++)
        {
            if (!fumeList[i].getIsActive())
            {
                fumeList[i].setActive(true);
            }
        }
        attackClock.restart();
    }
    for (int i = 0; i < 4; i++)
    {
        fumeList[i].update(window);
    }
    window.draw(img.sprite);
}

Fume& FumeShroom::getFume(int i)
{
    return fumeList[i];
}