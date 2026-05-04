#pragma once
#include "Img.h"
class ItemCard {
    protected:
        bool isLocked;
        int cost;
        int relatedActorID;
        Img img;
    public:
        ItemCard(int relatedActorIDp = -1, int cost = 50);
        ItemCard(const ItemCard &itemCard);
        ItemCard& operator=(const ItemCard &itemCard);
        void update(RenderWindow &window);      
        bool getIsLocked();
        void setIsLocked(bool isLocked);
        Img& getImg();

        int getID();

        int isClicked(RenderWindow &window, Event &e);  // 0: not clicked, else return actorID

        int getCost();
};

