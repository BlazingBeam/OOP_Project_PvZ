#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Coordinate.h"
using namespace std;
using namespace sf;
class Img {
protected:
    Clock animateClock; //clock for animation
    int frame;          //current frame
    int width;          //width and height of each frame (OPTIONAL)
    int height;         
    int offsetX;        //offset of the frame (OPTIONAL)
    int offsetY;
    Texture texture;    //texture or image itself e.g .png, .jpg
    string path;        //path to sprite

    //Use These if updateAnimation() is used
    int frames;         //number of frames in the sprite
    float animationCD;  //time interval between each frame


public:
    Sprite sprite;      //sprite

    Img(Sprite sprite = Sprite(), Texture texture = Texture(), string path = "");
    Img(const Img &img);
    Img(string path);
    Img& operator=(const Img &img);

    bool operator==(const Img &img);
    bool operator!=(const Img &img);

    bool operator==(const string &path);
    bool operator!=(const string &path);

    void operator()(string path);   //setImg
    void setImg(string path, int width = -1, int height = -1, int offsetX = 0, int offsetY = 0);       //setImg, if width or height is -1, then the whole image is used
    void setImg(Sprite sprite);     //setImg
    void setImg(Texture texture);   //setImg
    void setFrames(int frames, float animationCD);     //setFrames
    void setFrame(int frame);       //setFrame
    void updateAnimation(int frameWidth = 0, int frameHeight = 0);         //animation handling

    int getFrame();
    int getFrames();
};