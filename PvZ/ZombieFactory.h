#pragma once
#include "Zombie.h"
#include "SimpleZombie.h"
#include "FootballZombie.h"
#include "FlyingZombie.h"
#include "DancingZombie.h"
#include "Vec.h"
#include "Cell.h"
#include "BulletFactory.h"

#include "PlantFactory.h"
#include "LawnMower.h"
class ZombieFactory
{

protected:
    /*
    ZombieID's 33-36
    33: SimpleZombie
    34: FootballZombie
    35: FlyingZombie
    36: DancingZombie
    */
    Vec<Zombie*> zombieList;      //composition - ZombieFactory owns the plants - Zombie* because polymorphism



    bool allowedZombieID[4]; //Simple, Football, Flying, Dancing
    bool allowedRows[5]; //5 rows

    Clock zombieSpawnClock;
    double zombieSpawnDelay;    //initially 10 seconds

    PlantFactory* plantFactory; //aggregation - ZombieFactory uses PlantFactory
    LawnMower* lawnMowers;  //aggregation - ZombieFactory uses LawnMowers

    int &lives;
    int &currentLevel;
    int &score;

    int totalZombies;

	int zombiesKilled;
public:
    ZombieFactory(int &score, int &currentLevel, int &lives, PlantFactory* plantFactory = nullptr);
    ~ZombieFactory();

    void createZombie(int zombieID, int row, Cell cells[5][9], BulletFactory& bulletFactory, PlantFactory& plantFactory);

    void spawnZombie(bool allowedZombieID[4], Cell cells[5][9], BulletFactory& bulletFactory, PlantFactory& plantFactory);

    int zombieCleanup();

    void update(RenderWindow& window, Cell cells[5][9], BulletFactory& bulletFactory, PlantFactory& plantFactory);
    
    int getZombieCount();

    void handlePlantCollision(Cell cells[5][9]);

    void handleExplosion(Cell cells[5][9]);

    void handleWallnutRoll();

    void handleLawnMower();

    int getTotalZombies();

    int getZombiesKilled();

    void setLawnMowers(LawnMower lawnMowers[5]);

    void handleFumeShroom(Cell cells[5][9]);

    void setZombieSpawnDelay(double delay);

    double getZombieSpawnDelay();

};

