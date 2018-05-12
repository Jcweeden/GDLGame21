#ifndef _Vector2D_
#define _Vector2D_

class Vector2D {
public:

  Vector2D(int p_x, int p_y) {x = p_x; y = p_y;}
  
  int getX() {return x;}
  int getY() {return y;}
  
  int setX(float newX) {x = newX;}
  int setY(float newY) {y = newY;}


  friend Vector2D& operator+=(Vector2D& v1, const Vector2D v2)
  {
    v1.x += v2.x;
    v1.y += v2.y;

    return v1;
  }
  
protected:
  float x;
  float y;
};

#endif
