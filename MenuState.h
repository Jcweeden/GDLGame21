#ifndef _MENUSTATE_
#define _MENUSTATE_

#include "GameState.h"
//#include "GameObject.h"

#include <iostream>
#include <vector>

//class GameState;
class GameObject;

class MenuState : public GameState {
public:

  MenuState(){}
  
  virtual void update();
  virtual void render();

  virtual void onEnter();
  virtual void onExit();

  virtual std::string getStringID() {return menuStateID;}

  //virtual void callGameOver() {}

  
private:

  std::string calculateTimerScore(int time);
  
  static const std::string menuStateID;
  std::vector<GameObject*> gameObjects;
  /* Ball* ball; */
  /* Paddle* paddleTop; */
  /* Paddle* paddleBottom; */

  GameObject* logo;

  GameObject* pressToBeginImg;

  int timeAtStart;
  
};

#endif
