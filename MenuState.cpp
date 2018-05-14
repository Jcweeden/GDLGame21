#include "MenuState.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "SoundMixer.h"



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
    //gameObjects[0]->draw();
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), pressToPlayText, NULL, &pressToPlayRect); 
  }
  
  for (size_t i = 1; i < gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
  

  SDL_RenderCopy(TheGame::Instance()->getRenderer(), titleText, NULL, &titleRect); 
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), instructionsText, NULL, &instructionsRect); 

}


void MenuState::onEnter()
{
  TheSoundMixer::Instance()->playSound("menuScreen",0);
  timeAtStart = SDL_GetTicks();

  /*TheTextureManager::Instance()->load("assets/logo.png", "logoLarge", TheGame::Instance()->getRenderer());
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
  */

    fontTTF = TTF_OpenFont("Assets/ka1.ttf", 24);
    instructionFontTTF = TTF_OpenFont("Assets/ka1.ttf", 12);

    // if (fontTTF == NULL) {
    //  fprintf(stderr, "error: font not found\n");
    // }

  
  titleMessage = TTF_RenderText_Blended_Wrapped(fontTTF, "Zig- \n    Zag-\nPing- \n   Pong-", titleColour, 150); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  titleText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), titleMessage); 
  titleRect.x = (TheGame::Instance()->getWindowWidth()/2)- 225/2+55;  //controls the rect's x coordinate 
  titleRect.y = TheGame::Instance()->getUIHeight() + 45 + 54; // controls the rect's y coordinte
  titleRect.w = 300; // controls the width of the rect
  titleRect.h = 150; // controls the height of the rect
  
  
  pressToPlayMessage = TTF_RenderText_Blended_Wrapped(fontTTF, "PRESS RETURN\n        TO  PLAY", textColour,250); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  pressToPlayText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), pressToPlayMessage); 
  pressToPlayRect.x = (TheGame::Instance()->getWindowWidth()/2)- 300/2+55;  //controls the rect's x coordinate 
  pressToPlayRect.y = TheGame::Instance()->getWindowHeight() - 120+54; // controls the rect's y coordinte
  pressToPlayRect.w = 300; // controls the width of the rect
  pressToPlayRect.h = 80; // controls the height of the rect

  instructionsMessage = TTF_RenderText_Blended_Wrapped(instructionFontTTF, "1. Space to Zig-Zag the ball\n\n  2. Arrows to move paddles\n\n                   3. Time is score", textColour,250); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  instructionsText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), instructionsMessage); 
  instructionsRect.x = (TheGame::Instance()->getWindowWidth()/2)- 330/2+55;  //controls the rect's x coordinate 
  instructionsRect.y = 295+54; // controls the rect's y coordinte
  instructionsRect.w = 330; // controls the width of the rect
  instructionsRect.h = 170; // controls the height of the rect
}


void MenuState::onExit()
{
  for (size_t i; i < gameObjects.size(); i++) {
    gameObjects[i]->clean();
  }
  gameObjects.clear();

  SDL_DestroyTexture(titleText);
  SDL_DestroyTexture(pressToPlayText);
  SDL_DestroyTexture(instructionsText);

  
  
  //TheTextureManager::Instance()->clearFromTextureMap("ball");

}
