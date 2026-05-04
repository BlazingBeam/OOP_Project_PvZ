#include "Repeater.h"

Repeater::Repeater(Coordinate pos, BulletFactory& bulletFactory): Attack(&bulletFactory) {
    this->pos = pos;
    cost = 200;
    actorID = 17;

    img.setImg("Assets/Textures/Plants/Repeater/spritesheet.png");
    img.setFrames(15, 75);  //77 frames, 20 delay
    img.sprite.setTextureRect(IntRect(0, 0, 73, 71));

    doubleAttackDelay = 150;
    doubleAttackReady = false;
    doubleAttackClock.restart();
}

void Repeater::update(RenderWindow& window) {
	animateDamage();
    img.updateAnimation(73, 71);
    img.sprite.setPosition(pos.x, pos.y);
    
    if (attackClock.getElapsedTime().asMilliseconds() > attackDelay){
        rangedAttack(actorID, Coordinate(pos.x + 50, pos.y), Coordinate(1, 0));
        doubleAttackReady = true;
        doubleAttackClock.restart();
    }
    if (doubleAttackReady && doubleAttackClock.getElapsedTime().asMilliseconds() > doubleAttackDelay){
        forceRangedAttack(actorID, Coordinate(pos.x + 50, pos.y), Coordinate(1, 0));
        doubleAttackReady = false;
    }
    


    window.draw(img.sprite);
    // (debug) draw red box around plant
    // RectangleShape rect(Vector2f(80, 80));
    // rect.setPosition(pos.x, pos.y);
    // rect.setFillColor(Color::Transparent);
    // rect.setOutlineColor(Color::Red);
    // rect.setOutlineThickness(10);
    // window.draw(rect);
    // cout << "drawn at: " << pos.x << " " << pos.y << endl;
}