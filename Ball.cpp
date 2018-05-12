#include "Ball.h"
#include "SoundMixer.h"


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
    velocity.setY(2);
  }
  else
  {
    velocity.setY(-2);
  }

  if (horizontalDirection == RIGHT)
  {
    velocity.setX(-2);
  }
  else
  {
    velocity.setX(2);
  }

  GameObject::update();
  
}

void Ball::clean(){}


void Ball::handleInput()
{
  if (TheInputHandler::Instance()->getIsSpaceKeyPressed())
  {
    // std::cout << "Ball.cpp.handleInput(): space pressed - now zigging " << horizontalDirection << "\n";
    TheSoundMixer::Instance()->playSound("spaceBar", 0);
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
  TheSoundMixer::Instance()->playSound("hitPaddle", 0);
}

void Ball::reverseHoriztonalDirection(){
    if (horizontalDirection == LEFT)
  {
    horizontalDirection = RIGHT;
  }
  else
  {
    horizontalDirection = LEFT;
  }
}

  
