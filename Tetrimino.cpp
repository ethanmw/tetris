//Ethan Williams, final project: Tetris
//Tetrimino class definition

#include<cstdlib>
#include"Tetrimino.h"
#include"gfxnew.h"

Tetrimino::Tetrimino() {
  //Constructor
  //Randomly generates shape of tetrimino, sets spawn positions accordingly
  orientation = 0;
  int type = rand()%7;
  switch (type) {
    case 0:
      shape = 'I';
      for (int i = 0; i < 4; i++) x[i] = i+3;
      for (int i = 0; i < 4; i++) y[i] = 0;
      break;
    case 1:
      shape = 'O';
      x[0] = 4;
      x[1] = 5;
      x[2] = 4;
      x[3] = 5;
      y[0] = 0;
      y[1] = 0;
      y[2] = 1;
      y[3] = 1;
      break;
    case 2:
      shape = 'T';
      x[0] = 4;
      x[1] = 3;
      x[2] = 4;
      x[3] = 5;
      y[0] = 0;
      y[1] = 1;
      y[2] = 1;
      y[3] = 1;
      break;
    case 3:
      shape = 'J';
      x[0] = 3;
      x[1] = 3;
      x[2] = 4;
      x[3] = 5;
      y[0] = 0;
      y[1] = 1;
      y[2] = 1;
      y[3] = 1;
      break;
    case 4:
      shape = 'L';
      x[0] = 5;
      x[1] = 3;
      x[2] = 4;
      x[3] = 5;
      y[0] = 0;
      y[1] = 1;
      y[2] = 1;
      y[3] = 1;
      break;
    case 5:
      shape = 'S';
      x[0] = 4;
      x[1] = 5;
      x[2] = 3;
      x[3] = 4;
      y[0] = 0;
      y[1] = 0;
      y[2] = 1;
      y[3] = 1;
      break;
    case 6:
      shape = 'Z';
      x[0] = 3;
      x[1] = 4;
      x[2] = 4;
      x[3] = 5;
      y[0] = 0;
      y[1] = 0;
      y[2] = 1;
      y[3] = 1;
      break;
  }
}

Tetrimino::~Tetrimino() {};

char Tetrimino::getShape() {
  return shape;
}

int Tetrimino::getPosition(char axis, int index) {
  //returns x or y position of a block in the tetrimino
  if (axis == 'x') return x[index];
  else return y[index];
}

void Tetrimino::rotate() {
  //rotates the tetrimino if it is not an O (square)
  if (shape != 'O') {
    float origin_x, origin_y;
    switch (shape) {
      case 'L':
      case 'J':
      case 'Z':
      case 'T':
        origin_x = x[2];
        origin_y = y[2];
        break;
      case 'S':
        origin_x = x[3];
        origin_y = y[3];
        break;
      case 'I':
        switch (orientation) {
          case 0:
            origin_x = (x[1]+x[2])/2.0;
            origin_y = y[0]+.5;
            break;
          case 1:
            origin_x = x[0]-.5;
            origin_y = (y[1]+y[2])/2.0;
            break;
          case 2:
            origin_x = (x[1]+x[2])/2.0;
            origin_y = y[0]-.5;
            break;
          case 3:
            origin_x = x[0]+.5;
            origin_y = (y[1]+y[2])/2.0;
            break;
        }
        break;
    }
    for (int i = 0; i < 4; i++) {
      float x_original = x[i] - origin_x;
      float y_original = y[i] - origin_y;
      x[i] = -y_original + origin_x;
      y[i] = x_original + origin_y;
    }
    orientation = (orientation+1)%4;
    for (int i = 0; i < 4; i++) {
      while (x[i] < 0) slideRight();
      while (x[i] > 9) slideLeft();
    }
  }
}

void Tetrimino::slideLeft() {
  x[0] -= 1;
  x[1] -= 1;
  x[2] -= 1;
  x[3] -= 1;
}

void Tetrimino::slideRight() {
  x[0] += 1;
  x[1] += 1;
  x[2] += 1;
  x[3] += 1;
}

void Tetrimino::moveDown() {
  y[0] += 1;
  y[1] += 1;
  y[2] += 1;
  y[3] += 1;
}

void Tetrimino::draw() {
  //draws tetrimino to screen
  int wellcorner_x = 200;
  int wellcorner_y = 25;
  switch (shape) {
    case 'I':
      gfx_color(253,164,40); //orange
      break;
    case 'O':
      gfx_color(252,40,252); //magenta
      break;
    case 'T':
      gfx_color(45,255,254); //cyan
      break;
    case 'J':
      gfx_color(133,253,49); //lime
      break;
    case 'L':
      gfx_color(252,13,27); //red
      break;
    case 'S':
      gfx_color(255,253,56); //yellow
      break;
    case 'Z':
      gfx_color(11,36,251); //blue
      break;
  }
  for (int i = 0; i < 4; i++) {
    gfx_fill_rectangle(wellcorner_x+20*x[i]+1,wellcorner_y+20*y[i]+1,18,18);
  }
}

void Tetrimino::blackout() {
  //draws black over tetrimino to "erase" it, in preparation for movement
  int wellcorner_x = 200;
  int wellcorner_y = 25;
  gfx_color(0,0,0);
  for (int i = 0; i < 4; i++) {
    gfx_fill_rectangle(wellcorner_x+20*x[i]+1,wellcorner_y+20*y[i]+1,18,18);
  }
}
