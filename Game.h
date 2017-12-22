//Ethan Williams, final project: Tetris
//Game class interface
#include<array>
using namespace std;
#include "Tetrimino.h"

class Game {
public:
  Game();
  ~Game();

  int play();
  void blockLifeCycle();
  void commitTetrimino(Tetrimino);

  bool checkDown(Tetrimino);
  bool checkRight(Tetrimino);
  bool checkLeft(Tetrimino);
  bool checkRotate(Tetrimino);
  bool checkTopRow();
  bool rowIsFilled(int row);

  void draw();
  void drawUI();
  void clearRow(int row);

private:
  array<array<char, 20>, 10> well ;
  int score;
  double speed;
  char input;


};
