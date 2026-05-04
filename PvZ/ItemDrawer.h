#pragma once
#include "Img.h"
#include "ItemCard.h"
#include "PlantFactory.h"
#include "SunFactory.h"
class ItemDrawer {
    protected:
        Img frameImg;   //image of the frame that holds cards
        ItemCard itemCards[7];  //6 item cards

        int selectedID;   //selected itemID
        Sprite selectedSprite; //selected item sprite
        Texture selectedSpriteTexture;  //selected item texture

        Font currencyFont;
        Text currencyText;

        // SunFactory &sunFactory;
    public:
        ItemDrawer(SunFactory& sunFactory);
        void update(RenderWindow &window, Event &e, int &currentLevel, PlantFactory &plantFactory, Cell cells[5][9], BulletFactory& bulletFactory, SunFactory& sunFactory);

        int getActorID(int index);

        int getClickedActorID(RenderWindow &window, Event &e, int &currentLevel, SunFactory &sunFactory);

        void buildItemDrawer(int &currentLevel);

        void setSelected(int clickedID, int cost, Cell cells[5][9], Event &e, RenderWindow &window, PlantFactory &plantFactory, BulletFactory& bulletFactory, SunFactory &sunFactory);

        void drawSelected(RenderWindow &window, Cell cells[5][9]);

};