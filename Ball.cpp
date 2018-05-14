#include "Ball.h"
#include "SoundMixer.h"


Ball::Ball(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType)
    :GameObject(x, y, p_width, p_height, textureID, p_numFrames, p_resultOfCollisionType)
{
  verticalDirection = DOWN;
  horizontalDirection = RIGHT;
  gameOver = false;
  countdownToNextTrail = 50;
  lastFrameTime = 0;
}

void Ball::draw()
{

  for (size_t i = 0; i < ballTrails.size(); i++)
  {
    if (ballTrails[i]->getIsSpawning())
    {
      ballTrails[i]->draw();
    } else
    {
      //delete ballTrails[i];
      ballTrails.erase(ballTrails.begin()+i);
    }
  }

    GameObject::draw();

}

void Ball::update()
{

  for (size_t i = 0; i < ballTrails.size(); i++)
  {
    ballTrails[i]->update();
  }
  
  if (!gameOver) {
    handleInput();

    if (countdownToNextTrail < 0) { //time to spawn new obstacle
      ballTrails.push_back(new BallTrail(GameObject::position.getX(),GameObject::position.getY(), 22,22, "darkGreen",1,0));//new trail
      countdownToNextTrail = 50;
    }
    else
    {
      countdownToNextTrail -= (SDL_GetTicks() - lastFrameTime);
    }

    lastFrameTime = SDL_GetTicks();

    if (verticalDirection == DOWN)
    {
      velocity.setY(2.5);
    }
    else
    {
      velocity.setY(-2.5);
    }

    if (horizontalDirection == RIGHT)
    {
      velocity.setX(-2.5);
    }
    else
    {
      velocity.setX(2.5);
    }

    GameObject::update();
  }
  else
  {
    velocity.setX(0);
    velocity.setY(0);
  }
  
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

  
