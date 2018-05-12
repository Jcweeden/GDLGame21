#ifndef _IGameObject_
#define _IGameObject_
#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
//#include "Game.h"
//#include "LoaderParams.h"
#include <iostream>
#include <string>

enum resultOfCollide{
  NONE = 0,
  GAMEOVER = 1,
  BOUNCE = 2
};


class I_GameObject {

public:

  I_GameObject() {}
  
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

  virtual int resultOfCollision() {}

protected:

  int resultOfCollisionType;
  
  //virtual ~I_GameObject() {}

};

#endif
