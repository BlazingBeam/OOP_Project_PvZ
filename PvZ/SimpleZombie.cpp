#include "SimpleZombie.h"

SimpleZombie::SimpleZombie(int &lives, Coordinate pos, BulletFactory* bulletFactory, PlantFactory* plantFactory, double speed) : Zombie(bulletFactory, plantFactory), lives(lives) {
	this->pos = pos;
	this->actorID = 33;

	img.setImg("Assets/Textures/Zombies/NormalZombie/Zombie/spritesheet.png", 166, 144);
	// headFall.setImg("Assets/Textures/Zombies/NormalZombie/Head/spritesheet.png");
	img.sprite.setOrigin(100, 60);
	img.setFrames(22, 0.5/speed);  //22 frames, 20 delay
	img.sprite.setTextureRect(IntRect(0, 0, 166, 144));

	scoreValue = 10;

	health = 6;
	this->speed = speed;
	unitVelocity(-1, 0);
	
	Attack::attackDamage = 1;
}
void SimpleZombie::update(RenderWindow& window, Cell cells[][9]) {
	if (actorID == -1) return;
	// cout << status << endl;
	animateDamage();
	if (status == 2 && headFall && img != lostHeadAttack) {
		img = lostHeadAttack;
	}
	img.updateAnimation();
	img.sprite.setPosition(pos.x, pos.y);	//can adjust for speed
	// zombieAttack(Coordinate(pos.x, pos.y));
	//check if the next current cell is empty

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
					if (status != 2) {
						if (!headFall){
							img.setImg("Assets/Textures/Zombies/NormalZombie/ZombieAttack/spritesheet.png", 166, 144);
							// cout << "changed to attack" << endl;
							img.setFrames(21, 50);
						}
						else if (headFall) {
							img.setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHeadAttack/spritesheet.png", 166, 144);
							img.setFrames(11, 100);
						}
					}
					status = 2;
					break;
				}
			}
		}
		if (!collision) {
			if (status == 2) {
				if (!headFall) {
					img.setImg("Assets/Textures/Zombies/NormalZombie/Zombie/spritesheet.png", 166, 144);
					// cout << "changed to normal" << endl;
					img.setFrames(22, 1/speed);
				} 
				else {
					img.setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png", 166, 144);
					// cout << "changed to headLess" << endl;
					img.setFrames(18, 1.2/speed);
				}
				status = 0;
				unitVelocity(-1, 0);
			}
		} 
		else unitVelocity(0, 0);
	}
	
	if (status != -2) move(pos);



	if (headFall == 1) {
		head.sprite.setPosition(pos.x, pos.y);
		head.updateAnimation();
		window.draw(head.sprite);
		if (head.getFrame() == 11) headFall = -1;
	}
	if (status == -1 && img.getFrame() == img.getFrames() - 1) actorID = -1;
	if (status == -2 && img.getFrame() == img.getFrames() - 1) actorID = -1;
	window.draw(img.sprite);
}
