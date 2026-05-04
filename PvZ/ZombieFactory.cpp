#include "ZombieFactory.h"

/*
    ZombieID's 33-36
    33: SimpleZombie
    34: FootballZombie
    35: FlyingZombie
    36: DancingZombie
*/      


ZombieFactory::ZombieFactory(int &score, int &currentLevel, int &lives, PlantFactory* plantFactory): score(score), plantFactory(plantFactory), lives(lives), currentLevel(currentLevel) {
    this->zombieList = Vec<Zombie*>(100);

    allowedZombieID[0] = false;
    allowedZombieID[1] = false;
    allowedZombieID[2] = false;
    allowedZombieID[3] = false;

    allowedRows[0] = false;
    allowedRows[1] = false;
    allowedRows[2] = false;
    allowedRows[3] = false;
    allowedRows[4] = false;

    zombiesKilled = 0;

    switch (currentLevel) {
    case 1:
        zombieSpawnDelay = 17;
        totalZombies = 10;

        allowedZombieID[0] = true;

        allowedRows[0] = true;
        allowedRows[1] = true;
        allowedRows[2] = true;
        allowedRows[3] = true;
        allowedRows[4] = true;
        break;
    case 2:
        zombieSpawnDelay = 15;
        totalZombies = 20;

        allowedZombieID[0] = true;
        allowedZombieID[1] = true;
        allowedZombieID[2] = true;
        allowedZombieID[3] = true;

        allowedRows[0] = true;
        allowedRows[1] = true;
        allowedRows[2] = true;
        allowedRows[3] = true;
        allowedRows[4] = true;
    case 3:
        zombieSpawnDelay = 10;
        totalZombies = 30;
        
        allowedZombieID[0] = true;
        allowedZombieID[1] = true;
        allowedZombieID[2] = true;
        allowedZombieID[3] = true;

        allowedRows[0] = false;
        allowedRows[1] = false;
        allowedRows[2] = true;
        allowedRows[3] = false;
        allowedRows[4] = false;
        break;
    }


    if (plantFactory == nullptr) {
        cout << "Error: Plant Factory is null inside ZombieFactory" << endl;
        exit(1);
    }
}
ZombieFactory::~ZombieFactory() {
    zombieList.clear();
}

void ZombieFactory::createZombie(int zombieID, int row, Cell cells[5][9], BulletFactory& bulletFactory, PlantFactory& plantFactory) {
    Zombie* zombie = nullptr;
    // cout << cellX << " " << cellY << endl; //debug
    switch (zombieID) {
    case 33:
        zombie = new SimpleZombie(lives, Coordinate(1150, cells[row][0].pos.y), &bulletFactory, &plantFactory);
        break;
    case 34:
        zombie = new FootballZombie(lives, Coordinate(1150, cells[row][0].pos.y), &bulletFactory, &plantFactory, cells);
        break;
    case 35:
        zombie = new FlyingZombie(lives, Coordinate(1150, cells[row][0].pos.y), &bulletFactory);
        break;
    case 36:
        zombie = new DancingZombie(lives, Coordinate(1150, cells[row][0].pos.y), &zombieList, &bulletFactory, &plantFactory, cells);
        break;
   
    }
    if (zombie == nullptr) {
        return;
    }
    this->zombieList.push(zombie);
}

void ZombieFactory::spawnZombie(bool allowedZombieID[4], Cell cells[5][9], BulletFactory& bulletFactory, PlantFactory& plantFactory) {
    // cout << "Zombie Count: " << getZombieCount() << endl;
    // cout << "Total Zombie: " << totalZombies << endl;
    if ((getZombiesKilled() + getZombieCount()) >= totalZombies || zombieSpawnClock.getElapsedTime().asSeconds() < zombieSpawnDelay) {
        return;
    }
    // cout << "Zombie Spawned" << endl;
    int randRow = rand() % 5;
    do {
        randRow = rand() % 5;
        if (allowedRows[randRow]) {
            break;
        }
    } while (!allowedRows[randRow]);
    // cout << randRow << endl;
    int randZombie = 0;
    do {
        randZombie = rand() % 4;
        if (allowedZombieID[randZombie]) {
            createZombie(randZombie + 33, randRow, cells, bulletFactory, plantFactory);
            break;
        }
    } while (!allowedZombieID[randZombie]);

    zombieSpawnClock.restart();
}

int ZombieFactory::zombieCleanup() {
    int count = 0;
    for (int i = 0; i < this->zombieList.size(); ) {
        if (this->zombieList[i]->getActorID() == -1) {
            Zombie* zomb = zombieList[i];
            this->zombieList.popAt(i);    // Remove the element at index i
            score += zomb->getScoreValue();
            delete zomb;
            ++count; // Increment count for each deleted zombie
        } else {
            ++i; // Only increment i if no deletion occurred
        }
    }
    zombiesKilled += count;
    return count;
}

void ZombieFactory::update(RenderWindow &window, Cell cells[5][9], BulletFactory &bulletFactory, PlantFactory &plantFactory) {  //this function will update the zombies
    for (int row = 0; row < 5; row++) {
        spawnZombie(allowedZombieID, cells, bulletFactory, plantFactory);
        handlePlantCollision(cells);
        handleExplosion(cells);
        handleWallnutRoll();
        handleLawnMower();
        handleFumeShroom(cells);
        for (int i = 0; i < this->zombieList.length(); i++) {
            if (this->zombieList[i]->getActorID() == -1) {
                continue;
            }
            if (this->zombieList[i]->getPos().y >= cells[row][0].pos.y && this->zombieList[i]->getPos().y <= cells[row][0].pos.y + 98) {
                this->zombieList[i]->checkCollisionWithBullet();
                if (this->zombieList[i]->getActorID() == 33 || this->zombieList[i]->getActorID() == 34 || this->zombieList[i]->getActorID() == 36){
                    this->zombieList[i]->update(window, cells);
                }
                else if (this->zombieList[i]->getActorID() == 35) {
                    zombieList[i]->update(window);
                }
            }
        }
    }
}

int ZombieFactory::getZombieCount() {
    return zombieList.size();
}

void ZombieFactory::handlePlantCollision(Cell cells[5][9]) {    //this function will check if the zombie is on the same cell as the plant
    Vec<Plant*> plantList = plantFactory->getPlantList();
    for (int i = 0; i < this->zombieList.size(); i++) {
        if (this->zombieList[i]->getActorID() == -1 || this->zombieList[i]->getStatus() == -1) {
            continue;
        }
        if (this->zombieList[i]->getStatus() == 2){
            if (zombieList[i]->getAttackClock().getElapsedTime().asMilliseconds() > zombieList[i]->getAttackDelay()){
                for (int j = 0; j < plantList.size(); j++) {
                    Coordinate plantCellPos = plantList[j]->getCell(cells);
                    if (zombieList[i]->getPos().x >= cells[int(plantCellPos.y)][int(plantCellPos.x)].pos.x && zombieList[i]->getPos().x <= cells[int(plantCellPos.y)][int(plantCellPos.x)].pos.x + 80 && zombieList[i]->getPos().y == cells[int(plantCellPos.y)][int(plantCellPos.x)].pos.y){
                        plantList[j]->takeDamage(zombieList[i]->getAttackDamage());
                        // cout << "Plant Health: " << plantList[j]->getHealth() << endl;
                        // cout << "AttackDamage: " << zombieList[i]->getAttackDamage() << endl;
                        zombieList[i]->getAttackClock().restart();
                        plantList[j]->animateDamage(true);
                        if (plantList[j]->getHealth() <= 0){
                            plantList[j]->setActorID(-1);
                        }
                        // cout << "Plant Health: " << plantList[j]->getHealth() << endl;
                    }
                }
            }
        }
    }
}

void ZombieFactory::handleExplosion(Cell cells[5][9]){      //this function will check if the zombie is on the cherry bombs explosion radius
    Vec<Plant*> plantList = plantFactory->getPlantList();
    for (int i = 0; i < zombieList.size(); i++) {
        if (zombieList[i]->getStatus() == -1 || zombieList[i]->getStatus() == -2) continue;
        for (int j = 0; j < plantList.size(); j++) {
            if (plantList[j]->getActorID() == -10) {
                //check if zombie is on the same cell, or the ones adjecent to it including the diagonal ones
                //each cell is 80x100
                Coordinate plantCellPos = plantList[j]->getCell(cells);
                if (zombieList[i]->getPos().x >= cells[int(plantCellPos.y)][int(plantCellPos.x)].pos.x - 140 && zombieList[i]->getPos().x <= cells[int(plantCellPos.y)][int(plantCellPos.x)].pos.x + 140 && zombieList[i]->getPos().y >= cells[int(plantCellPos.y)][int(plantCellPos.x)].pos.y - 150 && zombieList[i]->getPos().y <= cells[int(plantCellPos.y)][int(plantCellPos.x)].pos.y + 150){
                    zombieList[i]->setStatus(-2);
                    zombieList[i]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/BoomDie/spritesheet.png", 166, 144);
                    zombieList[i]->getImg().setFrames(20, 75);
                    zombieList[i]->getImg().setFrame(0);
                    zombieList[i]->getImg().sprite.setScale(1, 1);
                    zombieList[i]->getImg().sprite.setOrigin(100, 60);
                    
                }
            }
        }
    }
}

void ZombieFactory::handleWallnutRoll() {
    //in this function, we will check if zombie is on the same pixel as the wallnut while managing cooldowns and such
    //if the zombie is on the same pixel, zombie will take damage thats it
    Vec<Plant*> plantList = plantFactory->getPlantList();
    for (int i = 0; i < zombieList.size(); i++) {
        if (zombieList[i]->getStatus() == -1 || zombieList[i]->getStatus() == -2) continue;
        for (int j = 0; j < plantList.size(); j++) {
            if (plantList[j]->getActorID() == 21 && plantList[j]->getIsRolling()) {
                if (zombieList[i]->getPos().y == plantList[j]->getPos().y && zombieList[i]->getPos().x >= plantList[j]->getPos().x && zombieList[i]->getPos().x <= plantList[j]->getPos().x + 5){
                    if (plantList[j]->getAttackClock().getElapsedTime().asSeconds() > plantList[j]->getAttackDelay()){
                        plantList[j]->getAttackClock().restart();
                        zombieList[i]->takeDamage(plantList[j]->getAttackDamage());
                        zombieList[i]->animateDamage(true, 1);
                        if (zombieList[i]->getHealth() <= 0) {
                            if (zombieList[i]->getImg() != "Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png") zombieList[i]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png", 166, 144);
                                // cout << "changed to dying" << endl;
                                zombieList[i]->getImg().setFrames(10, 50);
                                zombieList[i]->getImg().setFrame(0);
                                zombieList[i]->getImg().sprite.setScale(1, 1);
                                zombieList[i]->getImg().sprite.setOrigin(100, 60);
                                zombieList[i]->setStatus(-1);
                            if (zombieList[i]->getActorID() == 35) zombieList[i]->setActorID(-1);
                        }
                        if (zombieList[i]->getHeadFall() == 0 && zombieList[i]->getHealth() <= 4) {
                            zombieList[i]->setHeadFall(true);
                            if (zombieList[i]->getActorID() == 33) {
                                zombieList[i]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png", 166, 144);
                                // cout << "changed to headLess" << endl;
                                zombieList[i]->getImg().setFrames(18, 75);
                            }
                        }
                    }
                }
            }
        }
    }
}

int ZombieFactory::getTotalZombies()
{
    return totalZombies;
}

int ZombieFactory::getZombiesKilled()
{
    return zombiesKilled;
}

void ZombieFactory::setLawnMowers(LawnMower lawnMowers[5]) {
    this->lawnMowers = lawnMowers;
}


void ZombieFactory::handleLawnMower() {
    if (getZombieCount() == 0) return;
    if (lawnMowers == nullptr) return;
    //if zombies crossed x = 244 then activate the lawn mower
    for (int i = 0; i < zombieList.size(); i++) {
        if (zombieList[i]->getPos().x < 244) {
            for (int j = 0; j < 5; j++) {
                if (lawnMowers[j].getPos().y == zombieList[i]->getPos().y && !lawnMowers[j].getIsActive()) {
                    lawnMowers[j].use();
                    zombieList[i]->takeDamage(lawnMowers[j].getAttackDamage());
                    if (zombieList[i]->getHealth() <= 0) {
                        if (zombieList[i]->getImg() != "Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png") zombieList[i]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png", 166, 144);
                        // cout << "changed to dying" << endl;
                        zombieList[i]->getImg().setFrames(10, 50);
                        zombieList[i]->getImg().setFrame(0);
                        zombieList[i]->getImg().sprite.setScale(1, 1);
                        zombieList[i]->getImg().sprite.setOrigin(100, 60);
                        zombieList[i]->setStatus(-1);
                        if (zombieList[i]->getActorID() == 35) zombieList[i]->setActorID(-1);
                    }
                    if (zombieList[i]->getHeadFall() == 0 && zombieList[i]->getHealth() <= 4) {
                        zombieList[i]->setHeadFall(true);
                        if (zombieList[i]->getActorID() == 33) {
                            if (zombieList[i]->getImg() != "Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png") zombieList[i]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png", 166, 144);
                            // cout << "changed to headLess" << endl;
                            zombieList[i]->getImg().setFrames(18, 75);
                        }
                    }
                    
                }
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        if (lawnMowers[i].getIsActive()) {
            for (int j = 0; j < zombieList.size(); j++) {
                if (zombieList[j]->getPos().y == lawnMowers[i].getPos().y && zombieList[j]->getPos().x >= lawnMowers[i].getPos().x && zombieList[j]->getPos().x <= lawnMowers[i].getPos().x + 71) {
                    zombieList[j]->takeDamage(lawnMowers[i].getAttackDamage());
                    if (zombieList[j]->getHealth() <= 0) {
                        if (zombieList[j]->getImg() != "Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png") zombieList[j]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png", 166, 144);
                        // cout << "changed to dying" << endl;
                        zombieList[j]->getImg().setFrames(10, 50);
                        zombieList[j]->getImg().setFrame(0);
                        zombieList[j]->getImg().sprite.setScale(1, 1);
                        zombieList[j]->getImg().sprite.setOrigin(100, 60);
                        zombieList[j]->setStatus(-1);
                        if (zombieList[j]->getActorID() == 35) zombieList[j]->setActorID(-1);
                    }
                    if (zombieList[j]->getHeadFall() == 0 && zombieList[j]->getHealth() <= 4) {
                        zombieList[j]->setHeadFall(true);
                        if (zombieList[j]->getActorID() == 33) {
                            if (zombieList[j]->getImg() != "Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png") zombieList[j]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png", 166, 144);
                            // cout << "changed to headLess" << endl;
                            zombieList[j]->getImg().setFrames(18, 75);
                        }
                    }
                }
            }
        }
    }
}


void ZombieFactory::handleFumeShroom(Cell cells[][9]) {
    Vec<Plant*> plantList = plantFactory->getPlantList();
    for (int i = 0; i < plantList.size(); i++) {
        if (plantList[i]->getActorID() == 22){
            for (int j = 0; j < 4; j++) {
                FumeShroom* fumeShroom = (FumeShroom*)plantList[i];
                if (fumeShroom->getFume(j).getIsActive()) {
                    for (int k = 0; k < zombieList.size(); k++) {
                        if (zombieList[k]->getPos().x >= fumeShroom->getFume(j).getPos().x && zombieList[k]->getPos().x <= fumeShroom->getFume(j).getPos().x + 80 && zombieList[k]->getPos().y == fumeShroom->getFume(j).getPos().y && (fumeShroom->getFume(j).getAttackClock().getElapsedTime().asSeconds() > fumeShroom->getFume(j).getAttackDelay())){
                            zombieList[k]->takeDamage(1);
                            zombieList[k]->animateDamage(true, 1);
                            fumeShroom->getFume(j).getAttackClock().restart();
                            if (zombieList[k]->getHealth() <= 0) {
                                if (zombieList[k]->getImg() != "Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png") zombieList[k]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png", 166, 144);
                                // cout << "changed to dying" << endl;
                                zombieList[k]->getImg().setFrames(10, 50);
                                zombieList[k]->getImg().setFrame(0);
                                zombieList[k]->getImg().sprite.setScale(1, 1);
                                zombieList[k]->getImg().sprite.setOrigin(100, 60);
                                zombieList[k]->setStatus(-1);
                                if (zombieList[k]->getActorID() == 35) zombieList[k]->setActorID(-1);
                            }
                            if (zombieList[k]->getHeadFall() == 0 && zombieList[k]->getHealth() <= 4) {
                                zombieList[k]->setHeadFall(true);
                                if (zombieList[k]->getActorID() == 33) {
                                    if (zombieList[k]->getImg() != "Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png") zombieList[k]->getImg().setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png", 166, 144);
                                    // cout << "changed to headLess" << endl;
                                    zombieList[k]->getImg().setFrames(18, 75);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

double ZombieFactory::getZombieSpawnDelay() {
    return zombieSpawnDelay;
}

void ZombieFactory::setZombieSpawnDelay(double delay) {
    zombieSpawnDelay = delay;
}