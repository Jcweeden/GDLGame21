#include "Paddle.h"


Paddle::Paddle(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType)
    :GameObject(x, y, p_width, p_height, textureID, p_numFrames, p_resultOfCollisionType)
{

}

void Paddle::draw()
{
  GameObject::draw();
}

void Paddle::update()
{
  handleInput();
  GameObject::update();
}

void Paddle::clean(){}

void Paddle::handleInput()
{
  bool paddleMoving = false;
  
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
  {
    velocity.setX(-2);
    paddleMoving = true;
  }
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
  {
    velocity.setX(2);
    paddleMoving = true;
  }
    
  if(!paddleMoving)
  {
    velocity.setX(0);
  }
}
