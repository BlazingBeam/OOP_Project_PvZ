#include "CherryBomb.h"

CherryBomb::CherryBomb(Coordinate pos) {
    this->pos = pos;
    this->health = 100;
    this->actorID = 19;
    this->explosionRadius = 100;

    cost = 150;

    this->img.setImg("Assets/gifs/powie.png", 100, 100);
    this->img.sprite.setScale(2.5, 2.5);
    this->img.setFrames(31, 1500/18);
    img.sprite.setTextureRect(IntRect(0, 0, 100, 100));
    img.sprite.setOrigin(40, 40);
    img.setFrame(0);

}

void CherryBomb::update(RenderWindow& window) {
    if (img.getFrame() == 30) {
        actorID = -1;
    }
    if (img.getFrame() == 18) {
        actorID = -10;
    }
    img.updateAnimation();
    img.sprite.setPosition(pos.x, pos.y);
    window.draw(img.sprite);
    // (debug) draw red box around plant
    // RectangleShape rect(Vector2f(80, 80));
    // rect.setPosition(pos.x, pos.y);
    // rect.setFillColor(Color::Transparent);
    // rect.setOutlineColor(Color::Red);
    // rect.setOutlineThickness(10);
    // window.draw(rect);
    // cout << "drawn at: " << pos.x << " " << pos.y << endl;
}