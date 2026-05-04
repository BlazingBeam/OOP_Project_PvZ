#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(string playerName): currentLevel(1), ui(mode = 1, level->getSunFactory()) {
    buildLevel();
    srand(unsigned(time(nullptr)));
    this->playerName = playerName;

    winImg.setImg("Assets/ui/Victory.png");
    loseImg.setImg("Assets/ui/Defeat.png");
}

void Game::buildLevel() {
    switch (currentLevel) {
        case 1:
            level = new BeginnersGarden(currentLevel);
            break;
        case 2:
            level = new ZombieOutskirts(currentLevel);
            break;
        case 3:
            level = new SunflowerFields(currentLevel);
            break;
    }
    ui.buildGameUI(currentLevel);
}

void Game::setNameToFile() {
    //readfile of name "lb" and if not found create file and store playerName
    //if found, check if playerName is in the file
    //if not, add playerName to the file
    //if found, check if score is higher than the score in the file
    //if higher, update score
    //if not, do nothing
    //sort the file based on score

    ifstream file("lb.txt");
    string line;
    Vec<string> names;
    Vec<int> scores;
    bool found = false;
    while (getline(file, line)) {
        string name = "", scoreStr = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ':') {
                for (int j = i + 1; j < line.size(); j++) {
                    scoreStr += line[j];
                }
                break;
            }
            name += line[i];
        }
        int score = stoi(scoreStr);
        names.push(name);
        scores.push(score);
        if (name == playerName) {
            found = true;
            if (level->getScore() > score) {
                scores.pop();
                scores.push(level->getScore());
            }
        }
    }
    if (!found) {
        names.push(playerName);
        scores.push(level->getScore());
    }
    ofstream newFile("lb.txt"); //create new file
    //sort the file based on score
    for (int i = 0; i < scores.size(); i++) {
        for (int j = i + 1; j < scores.size(); j++) {
            if (scores[i] < scores[j]) {
                string tempName = names[i];
                names[i] = names[j];
                names[j] = tempName;
                int tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;
            }
        }
    }
    for (int i = 0; i < names.size(); i++) {
        if (scores[i] == 0) continue;
        newFile << names[i] << ":" << scores[i] << endl;
    }
    newFile.close();
    names.clear();
    scores.clear();
}

void Game::update(RenderWindow& window) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            setNameToFile();
            window.close();
        }
        if (debounce && debounceClock.getElapsedTime().asSeconds() > 0.2 || event.type == Event::KeyReleased){
            debounce = false;
        }
        if (!debounce && (event.type == 5 || event.type == 4)) {
            if ((event.type == 5 || event.type == 4) && (event.key.code == 13 || event.key.code == Keyboard::Enter) && (mode == 4 || mode == 5)) {
                mode = 1;
            }
            if (event.key.code == Keyboard::Escape && mode == 2) {
                mode = 0;   //PAUSE MODE
                debounce = true;
                cout << "PAUSE MODE" << endl;
                //pause all clocks from progressing
            }
            else if (event.key.code == Keyboard::Escape && mode == 0) {
                mode = 2;   //RESUME MODE
                debounce = true;
                cout << "RESUME MODE" << endl;
            }
        }
    }
    if (mode != 0) window.clear(); 
    if (mode == 4){
        window.draw(winImg.sprite);
        window.display(); 
        return;
    }
    if (mode == 5){
        window.draw(loseImg.sprite);
        window.display(); 
        return;
    }
    if (mode == 1) {
        ui.update(window, event, currentLevel, level->getPlantFactory(), level->getCells(), level->getBulletFactory(), level->getSunFactory());
        window.display(); 
        return;
    }
    if (mode == 2 && level != nullptr) {
        level->update(window, event);
        if (level->getZombiesKilled() == level->getTotalZombies() && level->getZombieCount() == 0) {
            currentLevel++;
            delete level;
            if (currentLevel > 3){
                currentLevel = 1;
                setNameToFile();
                mode = 4;
            }
            buildLevel();
        }
    }
    if (level->getLives() <= 0 && mode != 5) {
        delete level;
        currentLevel = 1;
        mode = 5;
        buildLevel();
    }
    // cout << "Lives: " << level->getLives() << endl;
    ui.update(window, event, currentLevel, level->getPlantFactory(), level->getCells(), level->getBulletFactory(), level->getSunFactory());
    window.display(); 
}