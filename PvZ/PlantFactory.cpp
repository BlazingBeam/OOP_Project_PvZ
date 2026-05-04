#include "PlantFactory.h"

/*
    PlantID's 16-32
    16: Peashooter
    17: Repeater
    18: Snowpea
    19: Cherrybomb
    20: Sunflower
    21: Wallnut
*/

PlantFactory::PlantFactory() {
    plantList = Vec<Plant*>(54);
}

PlantFactory::~PlantFactory() {
    plantList.clear();
}

void PlantFactory::createPlant(int plantID, int cellX, int cellY, Cell cells[5][9], BulletFactory& bulletFactory, SunFactory& sunFactory) {
    if (cells[cellY][cellX].getInUse()) {
        cout << "Error createPlant(): Cell at " << cellX << ", " << cellY << " is already in use" << endl;
        return;
    }
    Plant *plant = nullptr;
    switch (plantID) {
    case 16:
        plant = new Peashooter(cells[cellY][cellX].pos, bulletFactory);
        break;
    case 17:
        plant = new Repeater(cells[cellY][cellX].pos, bulletFactory);
        break;
    case 18:
        plant = new Snowpea(cells[cellY][cellX].pos, bulletFactory);
        break;
    case 19:
        plant = new CherryBomb(cells[cellY][cellX].pos);
        break;
    case 20:
        plant = new Sunflower(cells[cellY][cellX].pos, &sunFactory, cells);
        break;
    case 21:
        plant = new Wallnut(cells[cellY][cellX].pos);
        break;
    case 22:
        plant = new FumeShroom(cells[cellY][cellX].pos);
        break;
    }
    if (plant == nullptr) {
        return;
    }
    cells[cellY][cellX].setInUse(true);
    plantList.push(plant);
}

void PlantFactory::removePlant(int cellY, int cellX, Cell cells[5][9]) {
    if (!cells[cellY][cellX].getInUse()) {
        cout << "Error removePlant(): Plant at"<< cellX << ", " << cellY << " not found" << endl;
        return;
    }
    for (int i = 0; i < plantList.size(); i++) {
        if (plantList[i]->getPos() == cells[cellY][cellX].pos) {
            plantList[i]->setActorID(-1);
            delete plantList[i];
            plantList.popAt(i);
            cells[cellY][cellX].setInUse(false);
            return;
        }
    }
}

void PlantFactory::update(RenderWindow &window, Event &e, Cell cells[5][9]) {
    for (int i = 0; i < plantList.length(); i++) {
        // cout << plantList[i]->getActorID() << endl;
        switch (plantList[i]->getActorID()) {
            case 21:
                plantList[i]->update(window, e, cells);
                break;
            case -1:
                break;
            case 19:
            default:
                plantList[i]->update(window);
                break;
        }
    }
}

Vec<Plant*>& PlantFactory::getPlantList() {
    return plantList;
}

int PlantFactory::getPlantCount() {
    return plantList.length();
}

void PlantFactory::plantCleanup(Cell cells[5][9]) {
    bool cellDetected = false;
    for (int i = 0; i < plantList.length(); i++) {
        if (plantList[i]->getActorID() == -1) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 9; k++) {
                    if (cells[j][k].pos == plantList[i]->getPos()) {
                        cells[j][k].setInUse(false);
                        cellDetected = true;
                        break;
                    }
                }
                if (cellDetected) break;
            }
            delete plantList[i];
            plantList.popAt(i);
            i--;
        }
    }
}
