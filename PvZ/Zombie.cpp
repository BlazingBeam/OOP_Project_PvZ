#include "Zombie.h"

Zombie::Zombie(BulletFactory *bulletFactory, PlantFactory *PlantFactory) {
    this->status = 1;
    this->bulletFactory = bulletFactory;
    this->plantFactory = PlantFactory;
    head.setImg("Assets/Textures/Zombies/NormalZombie/ZombieHead/spritesheet.png", 150, 186);
    head.setFrames(12, 50);
    head.sprite.setTextureRect(IntRect(0, 0, -150, 186));
    headFall = false;

    lostHeadAttack.setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHeadAttack/spritesheet.png", 166, 144);
    lostHeadAttack.setFrames(11, 100);
}

void Zombie::checkCollisionWithBullet() {
    if (status == -1) return;
    Vec<Bullet*> bulletList = bulletFactory->getBulletList();
    for (int i = 0; i < bulletList.length(); i++) {
        if (bulletList[i]->getPos().x >= pos.x && bulletList[i]->getPos().x <= pos.x + 100 && bulletList[i]->getPos().y == pos.y) {
            takeDamage(bulletList[i]->getAttackDamage());
            if (bulletList[i]->getActorID() == 65) {
                animateDamage(true, 2);
                slowDown(0.5, 1.5, true);
            } 
            else {
                animateDamage(true, 1);
            } 
            if (headFall == 0 && health <= 5) {
                headFall = true;
                if (actorID == 33) {
                    if (img != "Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png") img.setImg("Assets/Textures/Zombies/NormalZombie/ZombieLostHead/spritesheet.png", 166, 144);
        			// cout << "changed to headLess" << endl;
                    img.setFrames(18, 1.2/speed);
                }
            }
            if (actorID == 34 && armor == 0){
                if (img != "Assets/Textures/Zombies/FootballZombie/spritesheet2.png") img.setImg("Assets/Textures/Zombies/FootballZombie/spritesheet2.png", 297, 221);
                img.setFrames(29, 1/speed);  // 29 frames, 40 pixels per frame
	            img.sprite.setScale(1, 1);
	            img.sprite.setOrigin(100, 80);
            }
            if (health <= 0) {
                if (img != "Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png") img.setImg("Assets/Textures/Zombies/NormalZombie/ZombieDie/spritesheet.png", 166, 144);
    			// cout << "changed to dying" << endl;
                img.setFrames(10, 50);
                img.setFrame(0);
                img.sprite.setScale(1, 1);
                img.sprite.setOrigin(100, 60);
                status = -1;
                if (actorID == 35) actorID = -1;
            }
            bulletList[i]->setActorID(-1);
            bulletFactory->bulletCleanup();
        }
    }
}

int Zombie::getStatus() {
    return status;
}

void Zombie::setStatus(int status)
{
    this->status = status;
}

int Zombie::getHeadFall()
{
    return headFall;
}

void Zombie::setHeadFall(int headFall)
{
    this->headFall = headFall;
}