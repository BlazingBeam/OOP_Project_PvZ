#pragma once
#include "Actor.h"
#include "BulletFactory.h"
#include "PlantFactory.h"
#include "Health.h"


class Zombie: public Actor, public Health, public Move, public Attack 
{
	protected:
		BulletFactory* bulletFactory;
		PlantFactory* plantFactory;

		Img head;
		int headFall; // 0 = false, 1 = true, -1 = stop animation

		Img lostHeadAttack;

		int status;
	public:
		Zombie(BulletFactory* bulletFactory = nullptr, PlantFactory* PlantFactory = nullptr);

		virtual ~Zombie() {};

		void checkCollisionWithBullet();

		int getStatus();
		
		void setStatus(int status);

		int getHeadFall();

		void setHeadFall(int headFall);
};

