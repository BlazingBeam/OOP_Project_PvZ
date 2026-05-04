#pragma once
#include "Sunflower.h"

Sunflower::Sunflower(Coordinate posP, SunFactory* sunFactoryP, Cell cells[][9]): sunFactory(sunFactoryP) {
    pos = posP;
    cost = 100;

    sunSpawnDelay = 10;

    img.setImg("Assets/Textures/Plants/Sunflower/spritesheet.png");
    img.setFrames(17, 75);
    img.sprite.setTextureRect(IntRect(0, 0, 73, 74));

    //if its inside a cell that has isSunlight = true, then it will generate sunlight 3x faster
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (cells[i][j].pos == pos) {
                if (cells[i][j].getIsSunlight()) sunSpawnDelay /= 2.0;
            }
        }
    }
}

void Sunflower::update(RenderWindow& window) {
    animateDamage();
    if (sunSpawnClock.getElapsedTime().asSeconds() > sunSpawnDelay) {
        sunFactory->spawnSun(pos);
        sunSpawnClock.restart();
    }
    img.updateAnimation(73, 74);
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