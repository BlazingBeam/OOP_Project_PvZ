#include "Snowpea.h"

Snowpea::Snowpea(Coordinate pos, BulletFactory& bulletFactory): Attack(&bulletFactory) {
    this->pos = pos;
    cost = 175;
    actorID = 18;

    img.setImg("Assets/Textures/Plants/Snowpea/spritesheet.png");
    img.setFrames(15, 75);  //77 frames, 20 delay
    img.sprite.setTextureRect(IntRect(0, 0, 71, 71));
}

void Snowpea::update(RenderWindow& window) {
	animateDamage();
    img.updateAnimation(71, 71);
    img.sprite.setPosition(pos.x, pos.y);
    rangedAttack(actorID, Coordinate(pos.x + 50, pos.y), Coordinate(1, 0));
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