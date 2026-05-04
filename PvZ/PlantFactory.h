#pragma once
#include "Plant.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "CherryBomb.h"
#include "Wallnut.h"
#include "Snowpea.h"
#include "Repeater.h"
#include "FumeShroom.h"

#include "Vec.h"
#include "Cell.h"
#include "BulletFactory.h"
#include "SunFactory.h"
/*
#include "Repeater.h"
#include "Snowpea.h"
#include "Cherrybomb.h"
#include "Wallnut.h"
*/
class PlantFactory {
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
    // ActorList* actorList;   //aggregated - PlantFactory uses ActorList
    Vec<Plant*> plantList;      //composed - PlantFactory owns the plants - Plant* because polymorphism
public:
    PlantFactory();
    ~PlantFactory();

    void createPlant(int plantID, int cellX, int cellY, Cell cells[5][9], BulletFactory& bulletFactory, SunFactory& sunFactory);
    void removePlant(int cellY, int cellX, Cell cells[5][9]);   

    void update(RenderWindow& window, Event &e, Cell cells[5][9]);

    Vec<Plant*>& getPlantList();

    int getPlantCount();

    void plantCleanup(Cell cells[5][9]);
};

