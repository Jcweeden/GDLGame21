#include "CollisionManager.h"
#include "SoundMixer.h"

#include <iostream>


CollisionManager* CollisionManager::s_pInstance = 0;

CollisionManager* CollisionManager::Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new CollisionManager();
      return s_pInstance;
    }

    return s_pInstance;
  }

void CollisionManager::checkForCollsionsAgainstBall(Ball* &ball, const std::vector<GameObject*> &objects)
{



  SDL_Rect* ballRect = new SDL_Rect();
  ballRect->x = ball->getPosition().getX();
  ballRect->y = ball->getPosition().getY();
  ballRect->w = ball->getWidth();
  ballRect->h = ball->getHeight();

  
  //for each obj
  for (size_t i = 0 ; i < objects.size(); i++) {
    //   std::cout << "Collision checking : " << i << "\n";

    SDL_Rect* objRect = new SDL_Rect();
    objRect->x = objects[i]->getPosition().getX();
    objRect->y = objects[i]->getPosition().getY();
    objRect->w = objects[i]->getWidth();
    objRect->h = objects[i]->getHeight();
    
    if (isColliding(ballRect, objRect))     //if there is a collision between the obj and the ball
    {
      std::cout << "Collision: " << objects[i]->resultOfCollision() << "\n";

        switch (objects[i]->resultOfCollision()) {
          case 0:
            std::cout << "NONE\n";
            break;
          case 1:
            std::cout << "GAMEOVER\n";
            SoundMixer::Instance()->playSound("death",0);
            break;
          case 2:
            std::cout << "BOUNCE\n";
            ball->reverseVerticalDirection();
            break;
        }       
    }
  }
}


bool CollisionManager::isColliding(SDL_Rect* ball, SDL_Rect* obj)
{
  int s_buffer = 4000;
  // std::cout << "obj->h : " << obj->h << "\n";
  //  std::cout << "ball->h : " << ball->h << "\n";

  int aHBuf = ball->h / s_buffer;
  int aWBuf = ball->w / s_buffer;
    
  int bHBuf = obj->h / s_buffer;
  int bWBuf = obj->w / s_buffer;

    // std::cout << "aHBuf : " << aHBuf << "\n";
  // std::cout << "bHBuf : " << bHBuf << "\n";

  
  // if the bottom of A is less than the top of B - no collision
  if((ball->y + ball->h) - aHBuf <= obj->y + bHBuf)  { return false; }
    
  // if the top of A is more than the bottom of B = no collision
  if(ball->y + aHBuf >= (obj->y + obj->h) - bHBuf)  { return false; }
    
  // if the right of A is less than the left of B - no collision
  if((ball->x + ball->w) - aWBuf <= obj->x +  bWBuf) { return false; }
    
  // if the left of A is more than the right of B - no collision
  if(ball->x + aWBuf >= (obj->x + obj->w) - bWBuf)  { return false; }
    
  // otherwise there has been a collision
  return true;
}


