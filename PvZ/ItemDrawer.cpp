#include "ItemDrawer.h"

ItemDrawer::ItemDrawer(SunFactory& sunFactory) {
    frameImg.setImg("Assets/ui/drawer_frame.png");
    /*
    PlantID's 16-32
    16: Peashooter      - 0
    17: Repeater        - 1 
    18: Snowpea         - 2
    19: Cherrybomb      - 3
    20: Sunflower       - 4
    21: Wallnut         - 5
    */
    frameImg.sprite.setPosition(0, 0);
    itemCards[0] = ItemCard(16, 100);   //Peashooter
    itemCards[1] = ItemCard(20, 100);   //Sunflower
    itemCards[2] = ItemCard(21, 50);    //Wallnut
    itemCards[3] = ItemCard(19, 150);   //Cherrybomb
    itemCards[4] = ItemCard(17, 200);   //Repeater
    itemCards[5] = ItemCard(18, 175);   //Snowpea
    itemCards[6] = ItemCard(22, 75);    //Fumeshroom
    for (int i = 0; i < 7; i++) {
        itemCards[i].getImg().sprite.setPosition(75 + 55*i, 7);
        itemCards[i].getImg().sprite.setScale(0.8, 0.8);
    }
    selectedID = 0;
    // selectedSprite.setScale(0, 0);
    // selectedSprite.setOrigin(0, 0);

    currencyFont.loadFromFile("Assets/Fonts/Samdan.ttf");
    currencyText.setFont(currencyFont);
    currencyText.setCharacterSize(20);
    currencyText.setFillColor(Color::White);
    currencyText.setOutlineColor(Color::Black);
    currencyText.setOutlineThickness(2);
    currencyText.setPosition(28, 60);
    currencyText.setString("0");
}

void ItemDrawer::update(RenderWindow &window, Event &e, int &currentLevel, PlantFactory &plantFactory, Cell cells[5][9], BulletFactory& bulletFactory, SunFactory &sunFactory) {
    window.draw(frameImg.sprite);
    for (int i = 0; i < 7; i++) {
        if (itemCards[i].getIsLocked()) continue;
        itemCards[i].update(window);
    }
    int id = getClickedActorID(window, e, currentLevel, sunFactory);
    int cost = 0;
    for (int i = 0; i < 7; i++) {
        if (itemCards[i].getID() == selectedID) {
            cost = itemCards[i].getCost();
            break;
        }
    }
    // cout << "cost:" << cost << endl;
    setSelected(id , cost, cells, e, window, plantFactory, bulletFactory, sunFactory);
    drawSelected(window, cells);
    currencyText.setString(to_string(sunFactory.getCurrency()));
    window.draw(currencyText);
}

int ItemDrawer::getActorID(int index) {
    return itemCards[index].getID();
}

int ItemDrawer::getClickedActorID(RenderWindow &window, Event &e, int &currentLevel, SunFactory &sunFactory) {
    double mousePosX = Mouse::getPosition().x;
    double mousePosY = Mouse::getPosition().y;
    //if right click pressed then selectedID = 0
    if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Right) {
        selectedID = 0;
        selectedSprite.setOrigin(0, 0);
        selectedSprite.setScale(1, 1);
    }
    for (int i = 0; i < 7; i++) {
        int id = itemCards[i].isClicked(window, e);
        if (id) {
            if (itemCards[i].getIsLocked()) return 0;
            if (sunFactory.getCurrency() < itemCards[i].getCost()) return 0;
            return id;
        }
    }
    return 0;
}

void ItemDrawer::buildItemDrawer(int &currentLevel) {
    for (int i = 0; i < 6; i++) {
        itemCards[i].setIsLocked(true);
    }
    switch (currentLevel){
        case 1:
            itemCards[0].setIsLocked(false);    //Peashooter
            itemCards[1].setIsLocked(false);    //Sunflower
            itemCards[2].setIsLocked(true);    //Wallnut
            itemCards[3].setIsLocked(true);    //Cherrybomb
            itemCards[4].setIsLocked(true);    //Repeater
            itemCards[5].setIsLocked(true);    //Snowpea
            itemCards[6].setIsLocked(true);    //Fumeshroom
            break;
        case 2:
            itemCards[0].setIsLocked(false);
            itemCards[1].setIsLocked(false);
            itemCards[2].setIsLocked(false);
            itemCards[3].setIsLocked(true);
            itemCards[4].setIsLocked(true);
            itemCards[5].setIsLocked(true);
            itemCards[6].setIsLocked(true);
            break;
        case 3:
            itemCards[0].setIsLocked(false);
            itemCards[1].setIsLocked(false);
            itemCards[2].setIsLocked(false);
            itemCards[3].setIsLocked(false);
            itemCards[4].setIsLocked(false);
            itemCards[5].setIsLocked(false);
            itemCards[6].setIsLocked(false);
            break;
    }
}

void ItemDrawer::setSelected(int clickedID, int cost, Cell cells[5][9], Event &e, RenderWindow &window, PlantFactory &plantFactory, BulletFactory& bulletFactory, SunFactory &sunFactory) {
    if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left && selectedID) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 9; j++) {
                if (cells[i][j].isMouseOver(window) && !cells[i][j].getInUse() && cells[i][j].getCanPlacePlant()) {
                    //if not enough currency, return
                    if (sunFactory.getCurrency() < cost) return;
                    sunFactory.setCurrency(sunFactory.getCurrency() - cost);
                    plantFactory.createPlant(selectedID, j, i, cells, bulletFactory, sunFactory);
                    selectedID = 0;
                    selectedSprite.setOrigin(0, 0);
                    selectedSprite.setScale(1, 1);
                    return;
                }
            }
        }
    }
    if (clickedID) {
        // plantFactory.createPlant(clickedID, 0, 0, cells);
        selectedID = clickedID;
        const unsigned short opacity = 150;
        switch (selectedID) {
            case 16:
                selectedSpriteTexture.loadFromFile("Assets/Textures/Plants/Peashooter/Peashooter_0.png");
                selectedSprite.setTexture(selectedSpriteTexture);
                selectedSprite.setTextureRect(IntRect(0, 0, 71, 71));
                selectedSprite.setColor(Color(255, 255, 255, opacity));
                break;
            case 17:
                selectedSpriteTexture.loadFromFile("Assets/Textures/Plants/Repeater/Repeater_0.png");
                selectedSprite.setTexture(selectedSpriteTexture);
                selectedSprite.setTextureRect(IntRect(0, 0, 71, 71));
                selectedSprite.setColor(Color(255, 255, 255, opacity));
                break;
            case 18:
                selectedSpriteTexture.loadFromFile("Assets/Textures/Plants/Snowpea/Snowpea_0.png");
                selectedSprite.setTexture(selectedSpriteTexture);
                selectedSprite.setTextureRect(IntRect(0, 0, 71, 71));
                selectedSprite.setColor(Color(255, 255, 255, opacity));
                break;
            case 19:
                selectedSpriteTexture.loadFromFile("Assets/Textures/Plants/Cherrybomb/Cherrybomb_0.png");
                selectedSprite.setTexture(selectedSpriteTexture);
                selectedSprite.setTextureRect(IntRect(0, 0, 112, 81));
                selectedSprite.setScale(0.8, 0.8);
                selectedSprite.setOrigin(28, 0);
                selectedSprite.setColor(Color(255, 255, 255, opacity));
                break;
            case 20:
                selectedSpriteTexture.loadFromFile("Assets/Textures/Plants/Sunflower/Sunflower_0.png");
                selectedSprite.setTexture(selectedSpriteTexture);
                selectedSprite.setColor(Color(255, 255, 255, opacity));
                break;
            case 21:
                selectedSpriteTexture.loadFromFile("Assets/Textures/Plants/Wallnut/Wallnut/Wallnut_0.png");
                selectedSprite.setTexture(selectedSpriteTexture);
                selectedSprite.setTextureRect(IntRect(0, 0, 65, 73));
                selectedSprite.setColor(Color(255, 255, 255, opacity));
                // selectedSprite.setScale(0.75, 0.75);
                break;
            case 22:
                selectedSpriteTexture.loadFromFile("Assets/Textures/Plants/PuffShroom/PuffShroom/spritesheet.png");
                selectedSprite.setTexture(selectedSpriteTexture);
                selectedSprite.setTextureRect(IntRect(0, 0,  40, 66));
                selectedSprite.setColor(Color(255, 255, 255, opacity));
                break;
        }
    }
}

void ItemDrawer::drawSelected(RenderWindow &window, Cell cells[5][9]) {
    if (!selectedID) return;
    float mousePosX = Mouse::getPosition(window).x;
    float mousePosY = Mouse::getPosition(window).y;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (cells[i][j].isMouseOver(window) && !cells[i][j].getInUse() && cells[i][j].getCanPlacePlant()) {
                selectedSprite.setPosition(cells[i][j].pos.x, cells[i][j].pos.y);
                window.draw(selectedSprite);
                return;
            }
        }
    }
    switch (selectedID) {
        case 16:
            selectedSprite.setPosition(mousePosX - 28, mousePosY - 35);
            break;
        case 17:
            selectedSprite.setPosition(mousePosX - 28, mousePosY - 35);
            break;
        case 18:
            selectedSprite.setPosition(mousePosX - 28, mousePosY - 35);
            break;
        case 19:
            selectedSprite.setPosition(mousePosX - 28, mousePosY - 35);
            break;
        case 20:
            selectedSprite.setPosition(mousePosX - 28, mousePosY - 35);
            break;
        case 21:
            selectedSprite.setPosition(mousePosX - 28, mousePosY - 35);
            break;
        case 22:
            selectedSprite.setPosition(mousePosX - 28, mousePosY - 35);
            break;
    }
    window.draw(selectedSprite);
}
