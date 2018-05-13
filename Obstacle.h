#ifndef _OBSTACLE_
#define _OBSTACLE_

#include "SDL2/SDL.h"

#include "GameObject.h"
#include "InputHandler.h"
#include <iostream>

class GameObject;


class Obstacle : public GameObject
{
public:

  Obstacle(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType);
  
  void draw();
  void update();
  void clean();
  
private:
  //  void handleInput();


};

#endif
