#include "FlyingZombie.h"

FlyingZombie::FlyingZombie(int &lives, Coordinate pos, BulletFactory* bulletFactory, double speed): Zombie(bulletFactory), lives(lives) {
	this->pos = pos;
	this->actorID = 35;

	img.setImg("Assets/Textures/Zombies/FlyingZombie/sprite.png");
	img.sprite.setScale(0.3, 0.3);
	img.sprite.setOrigin(0, 240);

	scoreValue = 15;

	this->speed = speed;
	unitVelocity(-1, 0);
}
void FlyingZombie::update(RenderWindow& window){
	animateDamage();
	if (status != -2) move(pos);
	if (pos.x <= 100) {
		actorID = -1;
		lives--;
	}
	img.sprite.setPosition(pos.x, pos.y);
	if (status == -2) {
		img.sprite.setScale(1, 1);
		img.sprite.setOrigin(100, 60);
		img.updateAnimation();
	}
	if (status == -2 && img.getFrame() == img.getFrames() - 1) actorID = -1;
	// zombieAttack(Coordinate(pos.x, pos.y));
	//draw rectangle on sprite

	window.draw(img.sprite);
}
