#include "GameUI.h"


GameUI::GameUI(SunFactory& sunFactory): itemDrawer(sunFactory) {}

void GameUI::update(RenderWindow &window, Event &e, int &currentLevel, PlantFactory &plantFactory, Cell cells[5][9], BulletFactory& bulletFactory, SunFactory& sunFactory) {
    itemDrawer.update(window, e, currentLevel, plantFactory, cells, bulletFactory, sunFactory);
}

void GameUI::buildGameUI(int &currentLevel) {
    itemDrawer.buildItemDrawer(currentLevel);
}
