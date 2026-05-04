#pragma once
#include <SFML/Graphics.hpp>
#include "Img.h"
#include "Vec.h"
#include <fstream>

using namespace sf;
class MenuUI {
protected:
    Img menu;    //background IMG
    int selection;
    bool debounce;
    Clock debounceTimer;

    Font font;

    Text StartButton;
    Text InstructionsButton;
    Text LeaderboardButton;
    Text ExitButton;

    bool insDisplayed;
    bool lbDisplayed;

    Img insImg; //instructions img
    Img lbImg;  //leaderboard img

    Text leaderboard1;
    Text leaderboard2;
    Text leaderboard3;
public:
    MenuUI();
    void update(RenderWindow& window, Event& e, int& mode);
    void updateSelection(RenderWindow& window, Event& e, int& mode);
};

