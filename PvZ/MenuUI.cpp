#include "MenuUI.h"

MenuUI::MenuUI() {
    selection = 1;
    menu.setImg("Assets/ui/MainMenu.jpg");

    menu.sprite.setScale(1080/1920.0, 1080/1920.0);

    StartButton.setString("Start");
    InstructionsButton.setString("Instructions");
    LeaderboardButton.setString("Leaderboard");
    ExitButton.setString("Exit");
    StartButton.setCharacterSize(50);
    InstructionsButton.setCharacterSize(50);
    LeaderboardButton.setCharacterSize(50);
    ExitButton.setCharacterSize(50);
    StartButton.setPosition(470, 200);
    InstructionsButton.setPosition(410, 300);
    LeaderboardButton.setPosition(420, 400);
    ExitButton.setPosition(475, 500);
    StartButton.setFillColor(Color::White);
    InstructionsButton.setFillColor(Color::White);
    LeaderboardButton.setFillColor(Color::White);
    ExitButton.setFillColor(Color::White);
    //make these outlined as well
    StartButton.setOutlineColor(Color::Black);
    InstructionsButton.setOutlineColor(Color::Black);
    LeaderboardButton.setOutlineColor(Color::Black);
    ExitButton.setOutlineColor(Color::Black);
    StartButton.setOutlineThickness(5);
    InstructionsButton.setOutlineThickness(5);
    LeaderboardButton.setOutlineThickness(5);
    ExitButton.setOutlineThickness(5);
    

    insDisplayed = false;
    insImg.setImg("Assets/ui/Instructions.png");
    insImg.sprite.setScale(0.9, 0.9);

    lbDisplayed = false;
    lbImg.setImg("Assets/ui/Leaderboardbadges.png");
    lbImg.sprite.setScale(0.9, 0.9);
    

    font.loadFromFile("Assets/fonts/Samdan.ttf");

    StartButton.setFont(font);
    InstructionsButton.setFont(font);
    LeaderboardButton.setFont(font);
    ExitButton.setFont(font);

    leaderboard1.setFont(font);
    leaderboard2.setFont(font);
    leaderboard3.setFont(font);
    leaderboard1.setCharacterSize(50);
    leaderboard2.setCharacterSize(50);
    leaderboard3.setCharacterSize(50);
    leaderboard1.setPosition(400, 140);
    leaderboard2.setPosition(400, 240);
    leaderboard3.setPosition(400, 340);
    leaderboard1.setFillColor(Color::White);
    leaderboard2.setFillColor(Color::White);
    leaderboard3.setFillColor(Color::White);
    leaderboard1.setOutlineColor(Color::Black);
    leaderboard2.setOutlineColor(Color::Black);
    leaderboard3.setOutlineColor(Color::Black);
    leaderboard1.setOutlineThickness(5);
    leaderboard2.setOutlineThickness(5);
    leaderboard3.setOutlineThickness(5);
    
    //read from file named lb.txt and display the top 3 scores
    ifstream file("lb.txt");
    string line;
    Vec<string> names;
    Vec<int> scores;
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
    }
    if (scores.size() > 0) {
        leaderboard1.setString("1. " + names[0] + " : " + to_string(scores[0]));
    }
    if (scores.size() > 1) {
        leaderboard2.setString("2. " + names[1] + " : " + to_string(scores[1]));
    }
    if (scores.size() > 2) {
        leaderboard3.setString("3. " + names[2] + " : " + to_string(scores[2]));
    }
    file.close();
}


void MenuUI::update(RenderWindow& window, Event& e, int& mode) {
    updateSelection(window, e, mode);
    if (insDisplayed) {
        window.draw(insImg.sprite);
        if (e.key.code == Keyboard::Escape) {
            insDisplayed = false;
        }
    }
    else if (lbDisplayed) {
        window.draw(lbImg.sprite);
        window.draw(leaderboard1);
        window.draw(leaderboard2);
        window.draw(leaderboard3);
        if (e.key.code == Keyboard::Escape) {
            lbDisplayed = false;
        }
    }
    else if (mode == 1) {
        window.draw(menu.sprite);
        window.draw(StartButton);
        window.draw(InstructionsButton);
        window.draw(LeaderboardButton);
        window.draw(ExitButton);
    }
}

void MenuUI::updateSelection(RenderWindow& window, Event& e, int& mode) {
    //underline selection
    if (selection == 1) {
        //underline StartButton
        StartButton.setStyle(sf::Text::Underlined);
        InstructionsButton.setStyle(sf::Text::Regular);
        LeaderboardButton.setStyle(sf::Text::Regular);
        ExitButton.setStyle(sf::Text::Regular);
    }
    if (selection == 2) {
        //underline InstructionsButton
        StartButton.setStyle(sf::Text::Regular);
        InstructionsButton.setStyle(sf::Text::Underlined);
        LeaderboardButton.setStyle(sf::Text::Regular);
        ExitButton.setStyle(sf::Text::Regular);
    }
    if (selection == 3) {
        //underline ExitButton
        StartButton.setStyle(sf::Text::Regular);
        InstructionsButton.setStyle(sf::Text::Regular);
        LeaderboardButton.setStyle(sf::Text::Underlined);
        ExitButton.setStyle(sf::Text::Regular);
    }
    if (selection == 4) {
        //underline ExitButton
        StartButton.setStyle(sf::Text::Regular);
        InstructionsButton.setStyle(sf::Text::Regular);
        LeaderboardButton.setStyle(sf::Text::Regular);
        ExitButton.setStyle(sf::Text::Underlined);
    }

    if (debounce && debounceTimer.getElapsedTime().asSeconds() > 0.2 || e.type == Event::KeyReleased){
        debounce = false;
    }
    // for my keyboard (MTyb) 4 and 5 are keyPressed
    if (!debounce && (e.type == Event::KeyPressed || e.type == 4)) {
        if (mode == 1){
            if (e.key.code == Keyboard::Up) {
                selection--;
                debounce = true;
                debounceTimer.restart();
            }
            else if (e.key.code == Keyboard::Down) {
                selection++;
                debounce = true;
                debounceTimer.restart();
            }
            
            if (selection < 1) {
                selection = 1;
            }
            else if (selection > 4) {
                selection = 4;
            }
            if (e.key.code == Keyboard::Space || e.key.code == 32) {
                if (selection == 1) {
                    mode = 2;
                    insDisplayed = false;
                    lbDisplayed = false;
                }
                if (selection == 2) {
                    insDisplayed = true;
                }
                if (selection == 3) {
                    lbDisplayed = true;
                }
                if (selection == 4) {
                    //exit
                    window.close();
                    exit(0);
                }
            }
        }
    }
}