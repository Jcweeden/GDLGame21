#ifndef _IGameObject_
#define _IGameObject_
#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
//#include "Game.h"
//#include "LoaderParams.h"
#include <iostream>
#include <string>

class I_GameObject {

public:
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

protected:

  //I_GameObject(/*const LoaderParams* pParams*/) {}
  //virtual ~I_GameObject() {}

};

#endif
