#pragma once  
#include "Cell.h"  
#include "Img.h"  
#include "Coordinate.h"  
#include "PlantFactory.h"  
#include "ZombieFactory.h"  
#include "SunFactory.h"  
#include "UI.h"  
class Level {  
protected:  
   int score;            //score of the player  
 
   Cell cells[5][9];            //5 lanes, 9 columns  
   Img bg;                    //sprite+texture+path+animation()  
   Coordinate pos;            //position of the bg  
 
   // ActorList actorList;    //list of all actors in the level  
   PlantFactory plantFactory;    //factory for creating plants  
   ZombieFactory zombieFactory;    //factory for creating zombies  
   BulletFactory bulletFactory;    //factory for creating bullets  
   SunFactory sunFactory;  
 
   int lives;    //original copy of lives  
   int &currentLevel;  
 
public:  
   Level(int &currentLevel);  
   Level(int &currentLevel, int totalWaveCount, Cell cells[5][9], Img bg);  
   virtual int getZombieCount() = 0;  
   virtual int getTotalZombies() = 0;  
   virtual void update(RenderWindow& window, Event &e, int mode = 0 );    //mode: 0: draw everything, -1: only bg  
 
   //byRef getters  
   Cell& getCell(int lane, int column);  
 
   //return the 2d array  
   Cell(*getCells())[9];  
 
   PlantFactory& getPlantFactory();  
   BulletFactory &getBulletFactory();  
   SunFactory &getSunFactory();  
 
   int getLives();  
   void setLives(int lives);  
 
   virtual int getZombiesKilled() = 0;  
 
   int getScore();  
};
