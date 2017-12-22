//Ethan Williams, final project: Tetris
//Tetrimino class interface
#include<array>
using namespace std;

class Tetrimino {
public:
  Tetrimino();
  //Tetrimino(char);
  ~Tetrimino();

  char getShape();
  int getPosition(char axis, int index);

  void rotate();
  void slideLeft();
  void slideRight();
  void moveDown();

  void blackout();
  void draw();

private:
  char shape;
  int orientation;
  array<int, 4> x;
  array<int, 4> y;
};
