#include "DancingZombie.h"

DancingZombie::DancingZombie(int &lives, Coordinate pos, Vec<Zombie*> *zombiesP, BulletFactory* bulletFactory, PlantFactory* plantFactory, Cell cells[][9], double speed) : Zombie(bulletFactory, plantFactory), zombies(zombiesP), lives(lives) {
	this->pos = pos;
	this->actorID = 36;

	this->bulletFactory = bulletFactory;
	this->plantFactory = plantFactory;

	img.setImg("Assets/Textures/Zombies/DancingZombie/spritesheet.png", 424, 722);
	img.setFrames(19, 1 / speed);  // 29 frames, 40 pixels per frame
	img.sprite.setTextureRect(IntRect(0, 0, 424, 722));
	img.sprite.setScale(0.2, 0.2);
	img.sprite.setOrigin(80, 250);

	health = 5;
	armor = 0;
	this->speed = speed;
	unitVelocity(-1, 0);

	scoreValue = 50;

	spawnDelay = 8;

	switchState = 0;
	switchCD = 5; //in seconds
	newRow = -1;

	Attack::attackDamage = 1;

	for (int i = 0; i < 5; i++) {
		if (pos.y == cells[i][0].pos.y) {
			currentRow = i; break;
		}
	}
}
void DancingZombie::update(RenderWindow& window, Cell cells[][9]) {
	animateDamage();
	img.updateAnimation();
	img.sprite.setPosition(pos.x, pos.y);

	if (pos.x <= 200 && status != -1) {
		if (img != "Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png") img.setImg("Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png", 166, 144);
		// cout << "changed to dying" << endl;
		img.setFrames(10, 50);
		img.setFrame(0);
		img.sprite.setScale(1, 1);
		img.sprite.setOrigin(100, 60);
		status = -1;
		lives--;
	}

	bool collision = false;	//if the zombie is colliding with a plant
	if (status != -1 && status != -2 && actorID != -1){
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				if (cells[i][j].getInUse() && pos.x >= cells[i][j].pos.x && pos.x <= cells[i][j].pos.x + 80 && pos.y == cells[i][j].pos.y || pos.x <= 200) {
					collision = true;
					status = 2;
					break;
				}
			}
		}
		if (!collision) {
			if (status == 2) {
				status = 0;
				unitVelocity(-1, 0);
			}
		} 
		else unitVelocity(0, 0);
	}
	

	spawnZombie(cells, bulletFactory, plantFactory);
	if (status == 0) switchLanes(cells);		//switch lanes if the zombie is not colliding with a plant
	if (status != -2 && status != -1) move(pos);				//move the zombie

	if (status == -1 && img.getFrame() == img.getFrames() - 1) actorID = -1;
	if (status == -2 && img.getFrame() == img.getFrames() - 1) actorID = -1;


	window.draw(img.sprite);
}

void DancingZombie::spawnZombie(Cell cells[][9], BulletFactory *bulletFactory, PlantFactory *plantFactory) {
	if (rand()%2 && (spawnClock.getElapsedTime().asSeconds() > spawnDelay)) {
		Zombie *zombie = nullptr;
		int row = rand() % 5;
		//validate row based on currentRow
		while (row == currentRow || (abs(row - currentRow) != 1)) {
			row = rand() % 5;
		}
		zombie = new SimpleZombie(lives, Coordinate(pos.x, cells[row][0].pos.y), bulletFactory, plantFactory);
		zombies->push(zombie);
		spawnClock.restart();
	}
}

void DancingZombie::switchLanes(Cell cells[][9]) {
	if (switchClock.getElapsedTime().asSeconds() > switchCD) {
		int nextState; 
		bool valid = false;
		do {
			nextState = -1 + rand() % 3;
			if (switchState == 0 && nextState == 0) {
				break;
			}
			if (nextState == -1 && currentRow != 0) {
				valid = true;
				break;
			}
			if (nextState == 1 && currentRow != 4) {
				valid = true;
				break;
			}
		} while (!valid);
		switchState = nextState;
		pos.y = cells[currentRow + switchState][0].pos.y;
		if (switchState != 0) if (pos.x - 80 >= cells[0][0].pos.x) pos.x -= 80;
		currentRow = currentRow + switchState;
		//move forward diagonally by adding 80 to x unless out of bounds
		
		switchClock.restart();
	}
}