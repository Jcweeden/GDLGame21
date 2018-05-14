#include "PlayState.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "MenuState.h"
#include "Obstacle.h"
#include "SoundMixer.h"
//#include "Vector2D.h"
#include <stdlib.h>     /* srand, rand */


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
    TheCollManager::Instance()->checkForCollsionsAgainstBall(ball, TheGame::Instance()->m_gameObjects); //check walls for collisions
    TheCollManager::Instance()->checkForCollsionsAgainstBall(ball, gameObjects); //check paddles and obstacles

    checkToSpawnNewObstacle();
    
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
    endGameEvents();
  }
}

void PlayState::endGameEvents()
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

void PlayState::checkToSpawnNewObstacle()
{
  
  if (countdownToNextObstacle < 0) { //time to spawn new obstacle
    spawnObstacle();
  }
  else
  {
    countdownToNextObstacle -= (SDL_GetTicks() - lastFrameTime);
  }

  lastFrameTime = SDL_GetTicks();
}

void PlayState::spawnObstacle()
{
  int widthHeight = calculateObstacleSpawnWidthHeight();
  Vector2D* spawnLocation = findSpawnLocation(widthHeight);
  
  gameObjects.push_back(new Obstacle(spawnLocation->getX()+55,spawnLocation->getY()+54, widthHeight,widthHeight, "redWall", 1, 0));

  timeToNextObstacle -= (timeToNextObstacle/25);
  countdownToNextObstacle = timeToNextObstacle;
  //std::cout << "next obstacle in: " << countdownToNextObstacle << "\n";
}

int PlayState::calculateObstacleSpawnWidthHeight()
{
  int widthHeight = 20; //base starting size

  int maxRand = (SDL_GetTicks() - gameStartTime)/1000;
  
  widthHeight += rand() % maxRand; 
  
  return widthHeight;
}

Vector2D* PlayState::findSpawnLocation(int widthHeight)
{
  int x = rand() % (maxX-minX-widthHeight) + minX; 
  int y = rand() % (maxY-minY-widthHeight) + minY; 

  return new Vector2D(x,y);
}

void PlayState::calculateObstacleSpawnBoundaries()
{
  int winWidth = TheGame::Instance()->getWindowWidth();
  int winHeight = TheGame::Instance()->getWindowHeight();

  int uiHeight = TheGame::Instance()->getUIHeight();
  int borderWidth = TheGame::Instance()->getBorderWidth();

  minX = 0 + borderWidth;
  maxX = winWidth - borderWidth;
  minY = uiHeight + borderWidth + paddleHeight + paddleBuffer + 5;
  maxY = winHeight - borderWidth - paddleHeight - paddleBuffer - 5; 
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
  timerScore.append(" . ");
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
  TheSoundMixer::Instance()->playSound("startGame",0);
  gameOver = false;
  triggerEndGame = false;
  highScoreUpdated = false;
  gameStartTime = SDL_GetTicks();
  endGameTime = 0;

  paddleWidth = 60;
  paddleHeight = 12;
  paddleBuffer = 5;
  
  numObstaclesSpawned = 0;
  timeToNextObstacle = countdownToNextObstacle = 3500;
  lastFrameTime = gameStartTime;
  calculateObstacleSpawnBoundaries();
  
  int ballWidthHeight = 22;
  TheTextureManager::Instance()->load("assets/lightGreen.png", "ball", TheGame::Instance()->getRenderer());
  ball = new Ball(((TheGame::Instance()->getWindowWidth()/2)+(ballWidthHeight/2))+55,
                   TheGame::Instance()->getUIHeight() + 30 + 54,
                   ballWidthHeight,
                   ballWidthHeight,
                   "ball",
                   4,
                   NONE);
  // gameObjects.push_back(ball);


  
  TheTextureManager::Instance()->load("assets/midGreen.png", "paddle", TheGame::Instance()->getRenderer());
  paddleTop = new Paddle((TheGame::Instance()->getWindowWidth()/2)-(paddleWidth/2)+ 55,
                         TheGame::Instance()->getBorderWidth() + TheGame::Instance()->getUIHeight() + paddleBuffer + 54,
                         paddleWidth,
                         paddleHeight,
                         "paddle",
                         1,
                         BOUNCE);
  paddleBottom = new Paddle((TheGame::Instance()->getWindowWidth()/2)-(paddleWidth/2) + 55,
                            (TheGame::Instance()->getWindowHeight())-TheGame::Instance()->getBorderWidth()-paddleHeight - paddleBuffer + 54,
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

