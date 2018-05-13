#include "MenuState.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"



const std::string MenuState::menuStateID = "MENU";


void MenuState::update ()
{  
  for (size_t i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }

  if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
  {
      TheGame::Instance()->getStateManager()->changeState(new PlayState());
  }

  
  TheGame::Instance()->getStateManager()->dequeueState();
  
}

void MenuState::render ()
{

  // std::cout << (SDL_GetTicks() - timeAtStart) % 500 << "\n";
  
  if (((SDL_GetTicks() - timeAtStart) % 2000) < 1250) {
    gameObjects[0]->draw();    
  }
  
  for (size_t i = 1; i < gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
}


void MenuState::onEnter()
{
  timeAtStart = SDL_GetTicks();

  TheTextureManager::Instance()->load("assets/logo.png", "logoLarge", TheGame::Instance()->getRenderer());
  logo = new GameObject((TheGame::Instance()->getWindowWidth()/2)-(277/2),
                                   (TheGame::Instance()->getWindowHeight() - TheGame::Instance()->getUIHeight())/3- (176/3),
                                   277,
                                   176 ,
                                   "logoLarge",
                                   1,
                                   0);


  
  TheTextureManager::Instance()->load("assets/PressToBegin.png", "pressToBeginImg", TheGame::Instance()->getRenderer());
  pressToBeginImg = new GameObject((TheGame::Instance()->getWindowWidth()/2)-(300/2),
                                   (TheGame::Instance()->getWindowHeight() - TheGame::Instance()->getUIHeight()) - 30,
                                   300,
                                   63 ,
                                   "pressToBeginImg",
                                   1,
                                   0);

  gameObjects.push_back(pressToBeginImg);
  gameObjects.push_back(logo);

}


void MenuState::onExit()
{
  for (size_t i; i < gameObjects.size(); i++) {
    gameObjects[i]->clean();
  }
  gameObjects.clear();
  
  //TheTextureManager::Instance()->clearFromTextureMap("ball");

}
