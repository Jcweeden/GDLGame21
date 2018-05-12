#include "GameStateManager.h"

std::vector<GameState*> gameStates;


void GameStateManager::update()
{
  if (!gameStates.empty()){
    gameStates.back()->update();
  }
}

void GameStateManager::render()
{
  if (gameStates.empty() == false){
    gameStates.back()->render();
  }
}


void GameStateManager::pushState(GameState* pState)
{
  gameStates.push_back(pState); //add 
  gameStates.back()->onEnter(); //run state init
}

void GameStateManager::changeState(GameState* pState)
{
  
}

void GameStateManager::popState()
{
  if (gameStates.empty() == false){
    gameStates.back()->onExit();
    delete gameStates.back();
    gameStates.pop_back();
  }
}

