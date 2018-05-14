#include "Obstacle.h"
#include "SoundMixer.h"


Obstacle::Obstacle(int x, int y, int p_width, int p_height, std::string textureID, int p_numFrames, int p_resultOfCollisionType)
    :GameObject(x, y, p_width, p_height, textureID, p_numFrames, p_resultOfCollisionType)
{
  isSpawning = false;
  spawnTimeStart = 0;
  initSpawn();
}


void Obstacle::initSpawn()
{
  render = false;
  isSpawning = true;
  spawnTimeStart = SDL_GetTicks();
}

void Obstacle::spawn()
{

  int timeSinceSpawn = SDL_GetTicks() - spawnTimeStart;

  if (timeSinceSpawn > 0 && timeSinceSpawn < 500)
  {
    render = true;
    //set colour
  }
  else if (timeSinceSpawn > 500 && timeSinceSpawn < 1000)
  {
    render = false;
    //set colour
  }
  else  if (timeSinceSpawn > 1000 && timeSinceSpawn < 1500)
  {
    render = true;
    //set colour
  }
  else if (timeSinceSpawn > 1500 && timeSinceSpawn < 2000)
  {
    render = false;
    //set colour
  }
  else {
    render = true;
    isSpawning = false;
    setCollisionType(1);//turn collider on
    TheSoundMixer::Instance()->playSpawned("spawned", 0);
  }
}

void Obstacle::draw()
{
  if (render) {
  GameObject::draw();
  }
}

void Obstacle::update()
{
  if(isSpawning)
  {
    spawn();
  }
  
  GameObject::update();
}

void Obstacle::clean()
{
  GameObject::clean();
}
