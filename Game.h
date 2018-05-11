#ifndef _Game_
#define _Game_
#include <SDL2/SDL.h>

#include "InputHandler.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class GameObject;

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

  std::vector<GameObject*> m_gameObjects;


  bool running() {return m_bRunning;}

private:

  Game() {}

  //static instance variable
  static Game* s_pInstance;
  
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
    
  bool m_bRunning;

  

};


typedef Game TheGame;

#endif
