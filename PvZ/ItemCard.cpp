#include "ItemCard.h"

ItemCard::ItemCard(int relatedActorIDp, int cost) : isLocked(true), cost(cost), relatedActorID(relatedActorIDp) {
    /*
    PlantID's 16-32
    16: Peashooter
    17: Repeater
    18: Snowpea
    19: Cherrybomb
    20: Sunflower
    21: Wallnut
    22: Fumeshroom
*/
    switch (relatedActorID){
        case 16:
            img.setImg("Assets/ui/Cards/peashooter.png");
            break;
        case 17:
            img.setImg("Assets/ui/Cards/repeater.png");
            break;
        case 18:
            img.setImg("Assets/ui/Cards/snowpea.png");
            break;
        case 19:
            img.setImg("Assets/ui/Cards/cherrybomb.png");
            break;
        case 20:
            img.setImg("Assets/ui/Cards/sunflower.png");
            break;
        case 21:
            img.setImg("Assets/ui/Cards/wallnut.png");
            break;
        case 22:
            img.setImg("Assets/ui/Cards/fumeshroom.png");
            break;
        }
}  

ItemCard::ItemCard(const ItemCard &itemCard) {
    isLocked = itemCard.isLocked;
    cost = itemCard.cost;
    relatedActorID = itemCard.relatedActorID;
    img = itemCard.img;
}

ItemCard& ItemCard::operator=(const ItemCard &itemCard) {
    if (this != &itemCard) {
        isLocked = itemCard.isLocked;
        cost = itemCard.cost;
        relatedActorID = itemCard.relatedActorID;
        img = itemCard.img;
    }
    return *this;
}

void ItemCard::update(RenderWindow &window) {
    window.draw(img.sprite);
}

bool ItemCard::getIsLocked() {
    return isLocked;
}

void ItemCard::setIsLocked(bool isLocked) {
    this->isLocked = isLocked;
}

Img& ItemCard::getImg() {
    return img;
}

int ItemCard::getID()
{
    return relatedActorID;
}

int ItemCard::isClicked(RenderWindow &window, Event &e) {
    float mousePosX = Mouse::getPosition(window).x;
    float mousePosY = Mouse::getPosition(window).y;
    if (mousePosX >= img.sprite.getPosition().x && mousePosX <= img.sprite.getPosition().x+51.2
        && mousePosY >= img.sprite.getPosition().y && mousePosY <= img.sprite.getPosition().y+72) {
        if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
            return relatedActorID;
        }
    }
    return false;
}

int ItemCard::getCost()
{
    return cost;
}
