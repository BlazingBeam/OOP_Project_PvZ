#pragma once
#include "Coordinate.h"
#include "Img.h"
#include "Cell.h"

class Actor {
protected:
    /*
    PlantID's 16-32
    16: Peashooter
    17: Repeater
    18: Snowpea
    19: Cherrybomb
    20: Sunflower
    21: Wallnut
    */
    static long long objects;

    int actorID;    
    Img img;
    Coordinate pos;

    int scoreValue;

    Clock animateDamageClock;
    double animateDamageColorPeakTime;
    bool isAnimatingDamage; 
    int damageColor;
public:
    Actor();
    virtual void update(RenderWindow &window);  //virtual function
    virtual void update(RenderWindow &window, Event &e, Cell cells[5][9]);  //virtual function (for wallnut)
    virtual void update(RenderWindow &window, Cell cells[5][9]);  //virtual function (for zombie)
    
    virtual ~Actor() = 0;

    int getActorID();
    Img& getImg();
    Coordinate& getPos();

    void setActorID(int actorID);

    void animateDamage(bool isAnimatingDamage = false, int damageType = 0); //1 = red, 2 = blue for frozen

    int getScoreValue();

    void setScoreValue(int scoreValue);

};



