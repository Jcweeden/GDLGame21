#ifndef _GAMESTATE_
#define _GAMESTATE_

#include <string>
#include <vector>


class GameState {

public:
  virtual void update() = 0;
  virtual void render() = 0;

  virtual void onEnter() = 0;
  virtual void onExit() = 0;

  virtual std::string getStringID() = 0;
};


#endif
