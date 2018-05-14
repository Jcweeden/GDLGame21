#ifndef _BallTrail_
#define _BallTrail_

#include "SDL2/SDL.h"

#include "GameObject.h"
#include "InputHandler.h"
#include <iostream>

class GameObject;

class BallTrail : public GameObject
{
public:
  BallTrail(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType);

  
void draw();
void update();
void clean();

bool getIsSpawning() {return isSpawning;}

virtual int resultOfCollision() { return 0;}

private:
  
  void spawn();
  
  bool isSpawning;
  int spawnTimeStart;
};

#endif
