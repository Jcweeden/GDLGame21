#include "BallTrail.h"

BallTrail::BallTrail(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType)
    :GameObject(x, y, p_width, p_height, textureID, p_numFrames, p_resultOfCollisionType)
{
  isSpawning = true;
  spawnTimeStart = 0;
  spawnTimeStart = SDL_GetTicks();
}

void BallTrail::spawn()
{
  int timeSinceSpawn = SDL_GetTicks() - spawnTimeStart;
  //std::cout<<"timeSinceSpawn: " << timeSinceSpawn;

  if (timeSinceSpawn > 0 && timeSinceSpawn < 80)
  {
    GameObject::setTextureID("whiteWall");
    GameObject::setHeight((22/4)*3);
    GameObject::setWidth((22/4)*3);
  }
  else if (timeSinceSpawn > 80 && timeSinceSpawn < 160)
  {
    GameObject::setTextureID("midGreen");
    GameObject::setHeight((22/4)*2);
    GameObject::setWidth((22/4)*2);
  }
  else  if (timeSinceSpawn > 160 && timeSinceSpawn < 240)
  {
    GameObject::setTextureID("lightGreen");
    GameObject::setHeight((22/4)*1);
    GameObject::setWidth((22/4)*1);
  }
  else {
    isSpawning = false;
  }
}

void BallTrail::update()
{
  if (isSpawning)
  {
    spawn();    
  }
  
    GameObject::update();
}

void BallTrail::draw()
{
  // std::cout<<"drawing trail\n";
  GameObject::draw();
}

void BallTrail::clean(){
  GameObject::clean();
}
