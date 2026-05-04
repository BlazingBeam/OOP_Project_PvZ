#include "Fume.h"

Fume::Fume(Coordinate pos)
{
    isActive = false;
    img.setImg("Assets/Textures/fog.png", 905, 780);
    img.sprite.setColor(Color(255, 0, 255, 1000));
    img.sprite.setScale(0.1, 0.1);

    this->pos = pos;
    lifetime = 0.5;
    attackDelay = 0.5;
}

void Fume::update(RenderWindow &window)
{
    if (isActive && lifetimeClock.getElapsedTime().asSeconds() > lifetime)
    {
        isActive = false;
    }
    if (isActive)
    {
        img.sprite.setPosition(pos.x, pos.y);
        window.draw(img.sprite);
    }
}

void Fume::setLifetime(double lifetime)
{
    this->lifetime = lifetime;
}

double Fume::getLifetime()
{
    return lifetime;
}

void Fume::setActive(bool isActive)
{
    this->isActive = isActive;
    lifetimeClock.restart();
}

bool Fume::getIsActive()
{
    return isActive;
}

void Fume::setIsActive(bool isActive) {
    this->isActive = isActive;
}
