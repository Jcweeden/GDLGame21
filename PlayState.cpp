#include "PlayState.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Game.h"
#include "Ball.h"


const std::string PlayState::playStateID = "PLAY";
std::vector<GameObject*> gameObjects;
Ball* ball;


void PlayState::update ()
{
  for (size_t i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }

  
  //loop through objects and check for collisions against the ball
  TheCollManager::Instance()->checkForCollsionsAgainstBall(ball, TheGame::Instance()->m_gameObjects);

}

void PlayState::render ()
{
  for (size_t i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
}

void PlayState::onEnter()
{
  TheTextureManager::Instance()->load("assets/white.png", "ball", TheGame::Instance()->getRenderer());
    ball = new Ball((680/2),30,22,22,"ball", 4, NONE);

    gameObjects.push_back(ball);


}


void PlayState::onExit()
{
  for (size_t i; i < gameObjects.size(); i++) {
    gameObjects[i]->clean();
  }
  gameObjects.clear();
  
  TheTextureManager::Instance()->clearFromTextureMap("ball");  
  
}
