#pragma once
#include "ItemDrawer.h"
class GameUI {
    protected:
        ItemDrawer itemDrawer;
    public:
        GameUI(SunFactory& sunFactory);
        void update(RenderWindow &window, Event &e, int &currentLevel, PlantFactory &plantFactory, Cell cells[5][9], BulletFactory& bulletFactory, SunFactory& sunFactory);
        void buildGameUI(int &currentLevel);    //build game UI based on currentLevel
};