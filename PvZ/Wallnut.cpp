#include "Wallnut.h"

Wallnut::Wallnut(Coordinate posP) {
    isRolling = false;
    pos = posP;
    cost = 50;

    actorID = 21;

    health = 6;
    spriteStatus = 3;

    attackDamage = 2;

    attackDelay = 0.3;

    img.setImg("Assets/Textures/Plants/Wallnut/WallNut/spritesheet.png");
    img.setFrames(16, 75);
    img.sprite.setTextureRect(IntRect(0, 0, 65, 73));
}

void Wallnut::update(RenderWindow& window, Event &e, Cell cells[5][9]) {
    roll(window, e, cells);
    switch (spriteStatus) {
        case 3:
            if (health <= 4 && health > 2) {
                img.setImg("Assets/Textures/Plants/Wallnut/WallNut/spritesheet3.png");
                img.setFrames(11, 100);
                spriteStatus = 2;
            }
            break;
        case 2:
            if (health <= 2 && health > 0) {
                img.setImg("Assets/Textures/Plants/Wallnut/WallNut/spritesheet4.png");
                img.setFrames(15, 75);
                spriteStatus = 0;
            }
            break;
    }
    img.updateAnimation(65, 73);
    img.sprite.setPosition(pos.x, pos.y);
    animateDamage();
    window.draw(img.sprite);
}

void Wallnut::roll(RenderWindow &window, Event &e, Cell cells[5][9])
{
    if (isRolling) health = 100;
    if (health <= 4) return;
    // cout << "e.mouseButton.button:" << e.mouseButton.button << endl;
    // cout << "e.type:" << e.type << endl;
    double mousePosX = Mouse::getPosition(window).x;
    double mousePosY = Mouse::getPosition(window).y;
    bool isOn = false;
    if (mousePosX >= pos.x && mousePosX <= pos.x + 65 && mousePosY >= pos.y && mousePosY <= pos.y + 73) {
        isOn = true;
    }
    if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Right && isOn && !isRolling) {
        isRolling = true;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                if (cells[i][j].pos == pos) {
                    cells[i][j].setInUse(false);
                    break;
                }
            }
        }
        img.setImg("Assets/Textures/Plants/Wallnut/WallNut/spritesheet2.png");
        img.setFrames(37, 30);
        img.setFrame(36);
        img.updateAnimation(65, 73);
        unitVelocity = Coordinate(1, 0);
        speed = 0.125;
    }
    if (isRolling) {
        move(pos);
        // attackMelee();
    }
    if (pos.x > 1080) {
        actorID = -1;
    }
}

bool Wallnut::getIsRolling()
{
    return isRolling;
}

double Wallnut::getAttackDamage()
{
    return attackDamage;
}

Clock& Wallnut::getAttackClock()
{
    return attackClock;
}

double Wallnut::getAttackDelay()
{
    return attackDelay;
}
