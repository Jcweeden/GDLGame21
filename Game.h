#ifndef _Game_
#define _Game_
#include "SDL2/SDL.h"

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
  
  std::vector<GameObject*> m_gameObjects; //walls

  SDL_Renderer* getRenderer() const { return m_pRenderer; }


  bool running() {return m_bRunning;}

private:

  Game() {}

  //static instance variable
  static Game* s_pInstance;
  
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
    

  Ball* ball;
  GameObject* screenOverlay;

  int windowWidth;
  int windowHeight;

  GameStateManager* m_pGameStateManager;

  //start the game loop
  bool m_bRunning;

};


typedef Game TheGame;

#endif
