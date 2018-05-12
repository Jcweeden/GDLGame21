#ifndef _GameObject_
#define _GameObject_
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Game.h"
#include "I_GameObject.h"
#include "Vector2D.h"
//#include "LoaderParams.h"
#include <iostream>
#include <string>


class GameObject : public I_GameObject {

public:

  GameObject( int x, int y, int p_width, int p_height, std::string textureID);

  
  virtual void draw();
  virtual void update();
  virtual void clean();



  Vector2D& getPosition() { return position; }
  int getWidth() { return width; }
  int getHeight() { return height; }
  
protected:

  virtual ~GameObject() {}

  
  int width;
  int height;

  Vector2D position;
  Vector2D velocity;
  Vector2D acceleration;

  
  int currentRow;
  int currentFrame;

  std::string textureID;

};

#endif
