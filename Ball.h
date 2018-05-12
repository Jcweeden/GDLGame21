#ifndef _Ball_
#define _Ball_

#include "SDL2/SDL.h"

#include "GameObject.h"
#include "InputHandler.h"
#include <iostream>

#include <iostream>

class GameObject;

class Ball : public GameObject
{
public:
Ball(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames);
  
  void draw();
  void update();
  void clean();

private:
  void handleInput();

//void reverseDirection();

  //~Ball();
};

#endif
