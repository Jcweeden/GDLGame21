#include "Ball.h"



Ball::Ball(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames)
    :GameObject(x, y, p_width, p_height, textureID, p_numFrames)
{
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

}

void Ball::clean(){}


void Ball::handleInput()
{
  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
  {
    std::cout << "Ball.cpp.handleInput(): space pressed\n";
    //reverse direction method
  }
 }


  
