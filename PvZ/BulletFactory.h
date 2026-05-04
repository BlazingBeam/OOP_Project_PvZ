#pragma once
#include "Vec.h"
#include "Cell.h"
#include "Bullet.h"
/*
#include "Repeater.h"
#include "Snowpea.h"
#include "Cherrybomb.h"
#include "Sunflower.h"
#include "Wallnut.h"
*/

class BulletFactory {
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
        // ActorList* actorList;   //aggregated
        Vec<Bullet*> bulletList;      //composed
    public:
        BulletFactory();
        ~BulletFactory();

        void createBullet(int plantID, Coordinate pos, Coordinate velocity = Coordinate());

        void update(RenderWindow& window);

        void bulletCleanup();

        Vec<Bullet*>& getBulletList();
};

