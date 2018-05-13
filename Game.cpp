#include "Game.h"
#include <iostream>
#include "SoundMixer.h"

#include "PlayState.h"
#include "MenuState.h"
#include "Ball.h"
#include "BounceSurface.h"
#include "CollisionManager.h"

Game* Game::s_pInstance = 0;

Game* Game::Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new Game();
      return s_pInstance;
    }

    return s_pInstance;
  }


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;

  if (fullscreen) {//if method parameter = true then make variable in line below
    flags = SDL_WINDOW_SHOWN;
  }
  
  // initialise SDL
   if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
   {
     std::cout << "Game: SDL init success\n";
     // if succeeded create our window
     m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
 
 // if the window creation succeeded create our renderer
     if(m_pWindow != 0)
     {
       std::cout << "Game: Window creation success\n";
       m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

       if (m_pRenderer != 0) {
         std::cout << "Game: Renderer creation success\n";
         SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
       }
       else {
         std::cout << "Game: Renderer init failed\n";
         return false;
       }
     }
     else
     {
       std::cout << "Game: Window init failed\n";
       return false;
     }
   }
   else
   {
     std::cout << "Game: SDL init failed\n";
     return false; // sdl could not initialise
   }

   std::cout << "Game: Init success\n";
   m_bRunning = true;//start the main loop

   highScore = 0;
   currentGameScore = 0;
   
   windowWidth = width;
   windowHeight = height;
   borderWidth = 10;
   UIHeight = 70;

   initText();
   loadSounds();
   loadTextures();
   loadObjects();

   m_pGameStateManager = new GameStateManager();
   
   //start on MenuState
   m_pGameStateManager->changeState(new MenuState());
   
   
   return true;
}

void Game::initText()
{

  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  
  fontTTF = TTF_OpenFont("Assets/ka1.ttf", 24);
  if (fontTTF == NULL) {
        fprintf(stderr, "error: font not found\n");
    }

  scoreMessage = TTF_RenderText_Solid(fontTTF, "SCORE: 00:00", textColour); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  scoreText = SDL_CreateTextureFromSurface(m_pRenderer, scoreMessage); 
  scoreRect.x = 0 + 30;  //controls the rect's x coordinate 
  scoreRect.y = 10; // controls the rect's y coordinte
  scoreRect.w = 150; // controls the width of the rect
  scoreRect.h = 50; // controls the height of the rect

  highScoreMessage = TTF_RenderText_Solid(fontTTF, "HIGH: 00:00", textColour); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  highScoreText = SDL_CreateTextureFromSurface(m_pRenderer, highScoreMessage); 
  highScoreRect.x = windowWidth-150-30;  //controls the rect's x coordinate 
  highScoreRect.y = 10; // controls the rect's y coordinte
  highScoreRect.w = 150; // controls the width of the rect
  highScoreRect.h = 50; // controls the height of the rect
}

//pass in 0 to update score, 1 to update highScore
void Game::updateScore(std::string text)
{  
  text.insert(0, "SCORE: ");
  scoreMessage = TTF_RenderText_Solid(fontTTF, text.c_str(), textColour);
  scoreText = SDL_CreateTextureFromSurface(m_pRenderer, scoreMessage); 
}

void Game::updateHighScore(int score, std::string text)
{
  std::cout << "new highscore: " << text << "\n";
  //std::cout << "running updateHighScore - old high: " << highScore << " new score: " << score <<  "\n";
  if (score > highScore) {
    highScore = score;
    text.insert(0, "HIGH: ");
    highScoreMessage = TTF_RenderText_Solid(fontTTF, text.c_str(), textColour);
    highScoreText = SDL_CreateTextureFromSurface(m_pRenderer, highScoreMessage);
  }
  else
  {
    //score was not highest
  }
}

void Game::loadSounds()
{
  TheSoundMixer::Instance()->load("assets/changeDirection.wav", "spaceBar", SOUND_SFX);
  TheSoundMixer::Instance()->load("assets/space.wav", "hitPaddle", SOUND_SFX);
  TheSoundMixer::Instance()->load("assets/death.wav", "death", SOUND_SFX);
}

void Game::loadTextures()
{
  TheTextureManager::Instance()->load("assets/darkGreen.png", "whiteWall", m_pRenderer);
  TheTextureManager::Instance()->load("assets/darkGreen.png", "redWall", m_pRenderer);
  TheTextureManager::Instance()->load("assets/overlayscreen.png", "overlayFilter", m_pRenderer);
  TheTextureManager::Instance()->load("assets/logo.png", "logo", m_pRenderer);  
}

void Game::loadObjects()
{  

  //WALLS
  m_gameObjects.push_back(new BounceSurface(0,UIHeight, windowWidth,borderWidth,"redWall",1,1)); //top wall
  m_gameObjects.push_back(new BounceSurface(0,(windowHeight-borderWidth), windowWidth,borderWidth,"redWall",1,1)); //bottom wall

  m_gameObjects.push_back(new BounceSurface(0,UIHeight, borderWidth,(windowHeight-borderWidth-borderWidth),"redWall",1,1)); //right wall
  m_gameObjects.push_back(new BounceSurface((windowWidth-borderWidth),UIHeight, borderWidth,(windowHeight-borderWidth-borderWidth),"redWall",1,1)); //left wall

  //LOGO
  //logo = new GameObject(200,0, 100,100,"logo",1,0); //Texture on screen

  //OVERLAY
  screenOverlay = new GameObject(0,0, windowWidth,windowHeight,"overlayFilter",1,0); //Texture on screen

}

void Game::render()
{
  SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour


  //draw background
  for(size_t i = 0; i < m_gameObjects.size(); i++)
  {
    m_gameObjects[i]->draw();
  }

  //draw game / menu
  m_pGameStateManager->render();

  //update score text
  
  SDL_RenderCopy(m_pRenderer, scoreText, NULL, &scoreRect); 

  //update highscore text
  SDL_RenderCopy(m_pRenderer, highScoreText, NULL, &highScoreRect); 


  //draw logo
  //logo->draw();
  
  //draw screen filter
  screenOverlay->draw();

  SDL_RenderPresent(m_pRenderer);  //draw to the screen
}

void Game::update() {
  //   m_currentFrame = int(((SDL_GetTicks() /100) % 6));

   //loop through and update our objects
   for(size_t i = 0; i < m_gameObjects.size(); i++)
   {
     m_gameObjects[i]->update();
   }

   m_pGameStateManager->update();

}

void Game::clean() {
  std::cout << "Game: cleaning game\n";

  //TheInputHandler::Instance()->clean();//remove any controller connections

  for (size_t i; i < m_gameObjects.size(); i++) {
    m_gameObjects[i]->clean();
  }

  screenOverlay->clean();
  //logo->clean();
  
  m_gameObjects.clear();

  //destroy fonts
  SDL_DestroyTexture(scoreText);
  SDL_DestroyTexture(highScoreText);
  TTF_Quit();

  
  SDL_DestroyWindow (m_pWindow);
  SDL_DestroyRenderer (m_pRenderer);
  SDL_Quit();
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();
}

void Game::quit() {
  m_bRunning = false;
}
