#pragma once
#include "BeginnersGarden.h"
#include "ZombieOutskirts.h"
#include "SunflowerFields.h"
#include "UI.h"
#include <fstream>


class Game {
protected:
    string playerName;

    Level* level;
    int currentLevel;     //=0
    UI ui;

    int mode;   // 0: Pause, 1: Menu, 2: Game, 3: EnterName
    bool debounce;

    Clock debounceClock;
    double debounceTimer;

    Img winImg;
    Img loseImg;
    //string resumeFileDir;   //="something.txt"
public:
    Game(string playerName = "...");
    void update(RenderWindow& window);
    void buildLevel();  //build level based on currentLevel

    void setNameToFile();
};