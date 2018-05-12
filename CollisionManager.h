#ifndef _COLLISIONMANAGER_
#define _COLLISIONMANAGER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameObject.h"
#include "Ball.h"

#include <vector>

class CollisionManager {


public:
    static CollisionManager* Instance();

    bool isColliding(SDL_Rect* ball, SDL_Rect* obj);

    
    void checkForCollsionsAgainstBall(Ball* &ball, const std::vector<GameObject*> &objects);

    
    
    //std::vector<GameObject*> &objects;

private:
    static CollisionManager* s_pInstance;
    
};

typedef CollisionManager TheCollManager;

#endif
