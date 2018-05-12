#ifndef _BounceSurface_
#define _BounceSurface_

#include "SDL2/SDL.h"

#include "GameObject.h"
#include <iostream>

class GameObject;

class BounceSurface : public GameObject{

public:

  BounceSurface(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType);
  
  void draw();
  void update();
  void clean();

protected:

  int resultOfCollisionType;
  
private:

  int resultOfCollision() {return resultOfCollisionType;}
};

#endif
