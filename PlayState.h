#ifndef _PLAYSTATE_
#define _PLAYSTATE_

#include "GameState.h"
//#include "GameObject.h"

#include <iostream>
#include <vector>

//class GameState;
class GameObject;
class Ball;
class Paddle;

class PlayState : public GameState {  
  
public:
  virtual void update();
  virtual void render();

  virtual void onEnter();
  virtual void onExit();

  virtual std::string getStringID() {return playStateID;}


private:
  static const std::string playStateID;
  std::vector<GameObject*> gameObjects;
  Ball* ball;
  Paddle* paddleTop;
  Paddle* paddleBottom;
};


#endif
