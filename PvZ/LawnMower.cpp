#include "LawnMower.h"

LawnMower::LawnMower(int row, Cell cells[5][9]) {
    this->isActive = false;
    pos.x = 210;
    this->pos.y = cells[row][0].pos.y;

    this->img.setImg("Assets/gifs/mower1.png", 71, 71);
    img.setFrames(1, 10000000);
    speed = 0;
    unitVelocity(1, 0);
    // pos.display();
    // cout << "LawnMower created" << endl;
}

void LawnMower::update(RenderWindow& window) {
    // pos.display();
    move(pos);
    img.updateAnimation();
    img.sprite.setPosition(pos.x, pos.y);
    window.draw(img.sprite);
    if (pos.x >= 1500) {
        speed = 0;
        // cout << "LawnMower reached end" << endl;
    }
    //debug draw collision box
    // RectangleShape rect(Vector2f(71, 71));
    // rect.setPosition(pos.x, pos.y);
    // rect.setFillColor(Color::Transparent);
    // rect.setOutlineColor(Color::Red);
    // rect.setOutlineThickness(1);
    // window.draw(rect);
}

void LawnMower::use() {
    img.setImg("Assets/gifs/mower2.png", 71, 71);
    img.setFrames(13, 20);
    isActive = true;
    unitVelocity(1, 0);
    speed = 1;
    attackDamage = 100;
}

bool LawnMower::getIsActive()
{
    return isActive;;
}
