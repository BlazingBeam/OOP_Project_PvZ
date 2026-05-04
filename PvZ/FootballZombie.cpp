#include "FootballZombie.h"

FootballZombie::FootballZombie(int &lives, Coordinate pos, BulletFactory* bulletFactory, PlantFactory* plantFactory, Cell cells[][9], double speed) : Zombie(bulletFactory, plantFactory), lives(lives) {
	this->pos = pos;
	this->actorID = 34;

	switchState = 0;
	switchCD = 5; //in seconds
	newRow = -1;

	img.setImg("Assets/Textures/Zombies/FootballZombie/spritesheet.png", 301, 312);
	img.setFrames(29, 1/speed);  // 29 frames, 40 pixels per frame
	img.sprite.setTextureRect(IntRect(0, 0, 301, 312));
	img.sprite.setScale(0.5, 0.5);
	img.sprite.setOrigin(120, 150);

	scoreValue = 30;

	health = 6;
	armor = 4;
	this->speed = speed;
	unitVelocity(-1, 0);

	Attack::attackDamage = 1;
	for (int i = 0; i < 5; i++) {
		if (pos.y == cells[i][0].pos.y) {
			currentRow = i; break;
		}
	}
}
void FootballZombie::update(RenderWindow& window, Cell cells[][9]) {
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
	if (status != -1 && status != -2){
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
	if (status == 0) switchLanes(cells);		//switch lanes if the zombie is not colliding with a plant
	if (status != -2) move(pos);				//move the zombie

	if (status == -1 && img.getFrame() == img.getFrames() - 1) actorID = -1;
	if (status == -2 && img.getFrame() == img.getFrames() - 1) actorID = -1;
	window.draw(img.sprite);
}

void FootballZombie::switchLanes(Cell cells[][9]) {
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
		currentRow = currentRow + switchState;
		switchClock.restart();
	}
}
