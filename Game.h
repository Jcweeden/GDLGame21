#ifndef _Game_
#define _Game_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "GameStateManager.h"
#include "InputHandler.h"
//#include "Ball.h"
#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>

class GameObject;
class Ball;

class Game
{
public:

  static Game* Instance();
        
  
  bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
  void render();
  void update();
  void handleEvents();
  void clean();

  void quit();

  void loadSounds();
  void loadTextures();
  void loadObjects();
  void initText();
  bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

  void updateScore(std::string text);
  void updateHighScore(int score, std::string text);

  
  std::vector<GameObject*> m_gameObjects; //walls

  SDL_Renderer* getRenderer() const { return m_pRenderer; }
  GameStateManager* getStateManager() {return m_pGameStateManager;}

  bool running() {return m_bRunning;}

  int getUIHeight(){return UIHeight;}
  int getWindowHeight(){return windowHeight;}
  int getWindowWidth(){return windowWidth;}
  int getBorderWidth(){return borderWidth;}
  
private:

  Game(){}

  //static instance variable
  static Game* s_pInstance;
  
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;


  

  Ball* ball;
  GameObject* logo;
  GameObject* screenOverlay;

  int windowWidth;
  int windowHeight;
  int borderWidth;
  int UIHeight;


  int highScore;
  int currentGameScore;
  
  GameStateManager* m_pGameStateManager;

  //start the game loop
  bool m_bRunning;


  //text
  TTF_Font* fontTTF; //this opens a font style and sets a size
  SDL_Color textColour = {40,104,19};  // this is the color in rgb format

  
  SDL_Surface* scoreMessage;
  SDL_Texture* scoreText; 
  SDL_Rect scoreRect;

  SDL_Surface* highScoreMessage;
  SDL_Texture* highScoreText;
  SDL_Rect highScoreRect;


};


typedef Game TheGame;

#endif
