#ifndef _GAMESTATE_
#define _GAMESTATE_

#include <string>
#include <vector>


class GameState {

public:

  GameState();
  
  virtual void update() = 0;
  virtual void render() = 0;

  virtual void onEnter() = 0;
  virtual void onExit() = 0;

  virtual std::string getStringID() = 0;

  bool getIsValid() const { return m_isValid; }
  void setIsValid(bool isValid) { m_isValid = isValid; }

  //virtual void callGameOver() = 0;
  
private:
  bool m_isValid;
};


#endif
