#include "Img.h"

Img::Img(Sprite sprite, Texture texture, string path) : sprite(sprite), texture(texture), path(path) {}

Img::Img(string path) : path(path) {
    texture.loadFromFile(path);
    sprite.setTexture(texture);
}

Img::Img(const Img &img) : path(img.path) {
    setImg(path);
}

Img& Img::operator=(const Img &img) {
    setImg(img.path, img.width, img.height);
    setFrames(img.frames, img.animationCD);
    return *this;
}

bool Img::operator==(const Img &img)
{
    return path == img.path;
}

bool Img::operator!=(const Img &img)
{
    return path != img.path;
}

bool Img::operator==(const string &path)
{
    return this->path == path;
}

bool Img::operator!=(const string &path)
{
    return this->path != path;
}

void Img::operator()(string path) {
    this->path = path;
    texture.loadFromFile(path);
    sprite.setTexture(texture);
}

void Img::setImg(string path, int width, int height, int offsetX, int offsetY) {
    this->path = path;
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    this->width = width;
    this->height = height;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    if (width != -1 && height != -1) sprite.setTextureRect(IntRect(offsetX, offsetY, width, height));
}

void Img::setImg(Sprite sprite) {
    this->sprite = sprite;
}

void Img::setImg(Texture texture) {
    this->texture = texture;
    sprite.setTexture(texture);
}

void Img::updateAnimation(int frameWidth, int frameHeight) {
    if (frameWidth == 0) frameWidth = width;
    if (frameHeight == 0) frameHeight = height;
    if (animateClock.getElapsedTime().asMilliseconds() > animationCD) {
        sprite.setTextureRect(IntRect(frame * frameWidth, offsetY, frameWidth, frameHeight));
        frame++; frame %= frames;
        animateClock.restart();
    }
}

int Img::getFrame()
{
    return frame;
}

int Img::getFrames(){
    return frames;
}

void Img::setFrames(int frames, float animationCD) {
    this->frames = frames;
    this->animationCD = animationCD;
}

void Img::setFrame(int frame) {
    this->frame = frame;
}
