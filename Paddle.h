#ifndef _Paddle_
#define _Paddle_

#include "SDL2/SDL.h"

#include "GameObject.h"
#include "InputHandler.h"
#include <iostream>

class GameObject;

class Paddle : public GameObject
{
public:
  Paddle(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType);
  
void draw();
void update();
void clean();

virtual int resultOfCollision() { return resultOfCollisionType;}


private:
void handleInput();


};

#endif
