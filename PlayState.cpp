#include "PlayState.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "MenuState.h"


const std::string PlayState::playStateID = "PLAY";

void PlayState::update ()
{
  for (size_t i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }
  ball->update();

  gameOver = ball->getGameOver();

  if (!gameOver) {
    //loop through objects and check for collisions against the ball
    TheCollManager::Instance()->checkForCollsionsAgainstBall(ball, TheGame::Instance()->m_gameObjects); //check walls for collisions
    TheCollManager::Instance()->checkForCollsionsAgainstBall(ball, gameObjects); //check paddles and obstacles

    TheGame::Instance()->updateScore(calculateTimerScore((SDL_GetTicks() - gameStartTime)/1000));

    TheGame::Instance()->getStateManager()->dequeueState();
  }
  else if (!triggerEndGame)
  {
    endGameTime = (SDL_GetTicks() - gameStartTime);
    triggerEndGame = true;
  }

  if(gameOver)
  {
    if (SDL_GetTicks() - (endGameTime+gameStartTime) > 1000 && !highScoreUpdated)
    {
      TheGame::Instance()->updateHighScore(endGameTime/1000, calculateTimerScore(endGameTime/1000));
      highScoreUpdated = true;
    }

    if (SDL_GetTicks() - (endGameTime+gameStartTime) > 3000)
    {
      TheGame::Instance()->getStateManager()->changeState(new MenuState());
    }
  }
}

std::string PlayState::calculateTimerScore(int time)
{
  int mins = time / 60;
  int seconds = time - (mins * 60);
  
  std::string timerScore = std::to_string(mins);

  if (mins < 10)
  {
    timerScore.insert(0, "0");
  }
  timerScore.append(":");
  if (seconds < 10)
  {
    timerScore.append("0");
  }

  timerScore.append(std::to_string(seconds));   
  
  return timerScore;
}

void PlayState::render ()
{
  for (size_t i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
  ball->draw();
}

void PlayState::onEnter()
{
  gameOver = false;
  triggerEndGame = false;
  highScoreUpdated = false;
  gameStartTime = SDL_GetTicks();
  endGameTime = 0;
  
  int ballWidthHeight = 22;
  TheTextureManager::Instance()->load("assets/lightGreen.png", "ball", TheGame::Instance()->getRenderer());
  ball = new Ball(((TheGame::Instance()->getWindowWidth()/2)+(ballWidthHeight/2)),
                   TheGame::Instance()->getUIHeight() + 30,
                   ballWidthHeight,
                   ballWidthHeight,
                   "ball",
                   4,
                   NONE);
  // gameObjects.push_back(ball);

  int paddleWidth = 90;
  int paddleHeight = 16;
  
  TheTextureManager::Instance()->load("assets/midGreen.png", "paddle", TheGame::Instance()->getRenderer());
  paddleTop = new Paddle((TheGame::Instance()->getWindowWidth()/2)-(paddleWidth/2),
                         TheGame::Instance()->getBorderWidth() + TheGame::Instance()->getUIHeight() + 5,
                         paddleWidth,
                         paddleHeight,
                         "paddle",
                         1,
                         BOUNCE);
  paddleBottom = new Paddle((TheGame::Instance()->getWindowWidth()/2)-(paddleWidth/2),
                            (TheGame::Instance()->getWindowHeight())-TheGame::Instance()->getBorderWidth()-paddleHeight - 5,
                            paddleWidth,
                            paddleHeight,
                            "paddle",
                            1,
                            BOUNCE);
  gameObjects.push_back(paddleTop);
  gameObjects.push_back(paddleBottom);

}


void PlayState::onExit()
{
  for (size_t i; i < gameObjects.size(); i++) {
    gameObjects[i]->clean();
  }
  gameObjects.clear();
  
  TheTextureManager::Instance()->clearFromTextureMap("ball");
  TheGame::Instance()->updateScore(calculateTimerScore(0) );

}

