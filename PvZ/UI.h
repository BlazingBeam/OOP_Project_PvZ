#pragma once
#include "MenuUI.h"
#include "GameUI.h"
#include "SunFactory.h"

using namespace sf;
class UI {
    protected:
        MenuUI menuUI;      //1
        GameUI gameUI;      //2

        int& mode; //byReference copy of Game's mode
    public:
        UI(int& mode, SunFactory &sunFactory);
        void update(RenderWindow &window, Event &e, int &currentLevel, PlantFactory &plantFactory, Cell cells[5][9], BulletFactory& BulletFactory, SunFactory& sunFactory);
        void buildGameUI(int &currentLevel);
};