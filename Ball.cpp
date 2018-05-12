#include "Ball.h"



Ball::Ball(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType)
    :GameObject(x, y, p_width, p_height, textureID, p_numFrames, p_resultOfCollisionType)
{
  verticalDirection = DOWN;
  horizontalDirection = RIGHT;  
}

void Ball::draw()
{
  GameObject::draw();
}

void Ball::update()
{
  handleInput();

  //incorporate speed of the ball
  currentFrame = int(((SDL_GetTicks() / 100) % 6));


  if (verticalDirection == DOWN)
  {
    velocity.setY(1);
  }
  else
  {
    velocity.setY(-1);
  }

  GameObject::update();
  
}

void Ball::clean(){}


void Ball::handleInput()
{
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
  {
    std::cout << "Ball.cpp.handleInput(): space pressed - now zigging " << horizontalDirection << "\n";
    reverseHoriztonalDirection();//reverse direction method
  }
 }

void Ball::reverseVerticalDirection(){
  if (verticalDirection == UP) {
    verticalDirection = DOWN;
  } else
  {
    verticalDirection = UP;
  }

}

void Ball::reverseHoriztonalDirection(){
    if (horizontalDirection == LEFT)
  {
    horizontalDirection = RIGHT;
    velocity.setY(-100);
  }
  else
  {
    horizontalDirection = LEFT;
    velocity.setY(100);
  }

}

  
