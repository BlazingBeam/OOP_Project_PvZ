#include "UI.h"

UI::UI(int& mode, SunFactory& sunFactory): mode(mode), gameUI(sunFactory) {}

void UI::update(RenderWindow &window, Event &e, int &currentLevel, PlantFactory &plantFactory, Cell cells[5][9], BulletFactory& bulletFactory, SunFactory& sunFactory) {
    // cout << mode << endl;
    switch(mode) {
        case 3:
        case 1:
            menuUI.update(window, e, mode);
            break;
        case 2:
            gameUI.update(window, e, currentLevel, plantFactory, cells, bulletFactory, sunFactory);
            break;
    }
}

void UI::buildGameUI(int &currentLevel) {
    gameUI.buildGameUI(currentLevel);
}
