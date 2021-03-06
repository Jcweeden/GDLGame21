#ifndef _Ball_
#define _Ball_

#include "SDL2/SDL.h"

#include "GameObject.h"
#include "BallTrail.h"

#include "InputHandler.h"
#include <iostream>

class GameObject;

enum ballHorizontalDirection
{
  LEFT = 0,
  RIGHT = 1
};

enum ballVerticalDirection
{
  UP = 0,
  DOWN = 1
};

class Ball : public GameObject
{
public:
  Ball(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType);
  
void draw();
void update();
void clean();

void reverseHoriztonalDirection();
void reverseVerticalDirection();
void setGameOver() { gameOver = true;}
bool getGameOver() { return gameOver;}

private:
void handleInput();

int verticalDirection;
int horizontalDirection;

int countdownToNextTrail;
int lastFrameTime;

bool gameOver;

  std::vector<BallTrail*> ballTrails;


};

#endif
