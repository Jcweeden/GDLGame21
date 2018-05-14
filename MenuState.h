#ifndef _MENUSTATE_
#define _MENUSTATE_

#include "GameState.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

//class GameState;
class GameObject;

class MenuState : public GameState {
public:

  MenuState(){}
  
  virtual void update();
  virtual void render();

  virtual void onEnter();
  virtual void onExit();

  virtual std::string getStringID() {return menuStateID;}

  //virtual void callGameOver() {}

  
private:

  std::string calculateTimerScore(int time);
  
  static const std::string menuStateID;
  std::vector<GameObject*> gameObjects;
  /* Ball* ball; */
  /* Paddle* paddleTop; */
  /* Paddle* paddleBottom; */

  GameObject* logo;

  GameObject* pressToBeginImg;

  int timeAtStart;


  //text
  TTF_Font* fontTTF; //this opens a font style and sets a size
  TTF_Font* instructionFontTTF; //this opens a font style and sets a size

  SDL_Color textColour = {40,104,19};  // this is the color in rgb format
  SDL_Color titleColour = {113,119,65};  // this is the color in rgb format

  
  SDL_Surface* titleMessage;
  SDL_Texture* titleText; 
  SDL_Rect titleRect;

  SDL_Surface* pressToPlayMessage;
  SDL_Texture* pressToPlayText;
  SDL_Rect pressToPlayRect;

  SDL_Surface* instructionsMessage;
  SDL_Texture* instructionsText;
  SDL_Rect instructionsRect;
};

#endif
