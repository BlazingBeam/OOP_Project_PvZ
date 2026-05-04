#include "Level.h"
#include "Peashooter.h"


Level::Level(int &currentLevel) : bg(), plantFactory(), bulletFactory(), sunFactory(0), currentLevel(currentLevel), zombieFactory(score, currentLevel, lives, &plantFactory) {
    lives = 3;
    srand(unsigned(time(nullptr)));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            //each cell is 80x100 starting at 264, 100
            cells[i][j].pos = Coordinate(264 + j * 80, 100 + i * 95);
            cells[i][j].setInUse(false);
        }
    }
}

Level::Level(int &currentLevel, int totalWaveCount, Cell cells[5][9], Img bg) : bg(bg), plantFactory(), bulletFactory(), sunFactory(), currentLevel(currentLevel), zombieFactory(score, currentLevel, lives, &plantFactory) {
    lives = 3;
    srand(unsigned(time(nullptr)));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            //each cell is 80x100 starting at 264, 100
            cells[i][j].pos = Coordinate(264 + j * 80, 100 + i * 95);
            cells[i][j].setInUse(false);
        }
    }
}

int Level::getZombieCount() {
    return zombieFactory.getZombieCount();
}

int Level::getTotalZombies()
{
    return zombieFactory.getTotalZombies();
}

void Level::update(RenderWindow& window, Event &e, int mode) {
    bg.sprite.setPosition(pos.x, pos.y);
    window.draw(bg.sprite);
    if (mode == -1) return;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (cells[i][j].getIsSunlight()) {
                CircleShape circle(30);
                circle.setFillColor(Color(255, 255, 255, 100));
                circle.setPosition(cells[i][j].pos.x, cells[i][j].pos.y);
                window.draw(circle);
            }
        }
    }
    plantFactory.update(window, e, cells);
    plantFactory.plantCleanup(cells);
    bulletFactory.update(window);
    bulletFactory.bulletCleanup();
    zombieFactory.update(window, cells, bulletFactory, plantFactory);
    zombieFactory.zombieCleanup();
    sunFactory.update(window, cells, e);
}

Cell& Level::getCell(int lane, int column) {
    return cells[lane][column];
}

Cell(*Level::getCells())[9] {
    return cells;
}

PlantFactory& Level::getPlantFactory() {
    return plantFactory;
}

BulletFactory& Level::getBulletFactory() {
    return bulletFactory;
}

SunFactory &Level::getSunFactory() {
    return sunFactory;
}

int Level::getLives()
{
    return lives;
}

void Level::setLives(int lives)
{
    this->lives = lives;
}

int Level::getZombiesKilled()
{
    return zombieFactory.getZombiesKilled();
}

int Level::getScore()
{
    return score;
}
