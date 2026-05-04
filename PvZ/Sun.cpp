#include "Sun.h"

Sun::Sun(int value, Coordinate pos, Coordinate unitVelocity, Coordinate* target): Move(unitVelocity, target), value(value) {
    this->pos = pos;
    actorID = 8;
    speed = 0.125;

    img.setImg("Assets/Textures/Spritesheets/sun.png");
    img.setFrames(22, 50);
    img.sprite.setTextureRect(sf::IntRect(0, 0, 71, 71));
}

void Sun::update(RenderWindow &window) {
    move(pos);
    img.updateAnimation(71, 71);
    img.sprite.setPosition(pos.x, pos.y);
    window.draw(img.sprite);
}

bool Sun::isMouseOver(RenderWindow& window) {
    Coordinate MousePos(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
    if ((MousePos.x >= pos.x && MousePos.x <= pos.x+71) && (MousePos.y >= pos.y && MousePos.y <= pos.y+71)) return true;
    return false;
}

int Sun::getValue() {
    return value;
}


