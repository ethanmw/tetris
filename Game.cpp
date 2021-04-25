//Ethan Williams, final project: Tetris
//Game class definition (handles gameboard ("Well"), gameplay mechanics)
#include <cstdio>
#include <ctime>
#include "gfxnew.h"
#include "Game.h"

Game::Game() {
  //Constructor
  speed = 800000;
  for (int i = 0; i < 10; i++) {
    well[i].fill(' ');
  }
}
Game::~Game() {}

int Game::play() {
  //main gameplay method
  score = 0;
  bool topisclear = true;
  while (topisclear) {
    blockLifeCycle();
    if (input == 27) return -1;
    for (int r = 0; r < 20; r++) {
      if (rowIsFilled(r)) clearRow(r);
    }
    if (!checkTopRow()) topisclear = false;
  }
  return score;
}

bool Game::checkTopRow() {
  //Checks to see if top row has a block in it to end the game
  bool topisclear = true;
  for (int col = 0; col < 10; col++) {
    if (well[col][0] != ' ') topisclear = false;
  }
  return topisclear;
}

bool Game::rowIsFilled(int row) {
  //Checks to see if row is filled and needs to be cleared
  bool filled = true;
  for (int col = 0; col < 10; col++) {
    if (well[col][row] == ' ') filled = false;
  }
  return filled;
}

void Game::clearRow(int row) {
  //Clears a filled row, shifts blocks down
  for (int col = 0; col < 10; col++) {
    for (int r = row; r > 0; r--) {
      well[col][r] = well[col][r-1];
    }
  }
  score++;
  if (score%10 == 0) speed *= .8;
}

void Game::blockLifeCycle() {
  //handles "life" of a tetrimino, from instantiation, falling down, to hitting bottom and being committed to well array
  Tetrimino block;
  draw();
  block.draw();
  bool hitbottom = false;
  input = 0;
  clock_t start = clock();
  while (!hitbottom) {
    while(gfx_event_waiting() != 0) {
      if (gfx_event_waiting() == 1) {
        input = gfx_wait();
        block.blackout();
        switch (input) {
          case 'a':
            if (checkLeft(block)) block.slideLeft();
            break;
          case 'd':
            if (checkRight(block)) block.slideRight();
            break;
          case 's':
            if (checkDown(block)) block.moveDown();
            break;
          case 'w':
            if (checkRotate(block)) block.rotate();
            break;
          case ' ':
            while(checkDown(block)) block.moveDown();
            break;
          case 27: //Escape
            return;
            break;
        }
        block.draw();;
        gfx_flush();
      } else gfx_wait();
    }
    if ((clock() - start) > speed) {
      block.blackout();
      if (checkDown(block)) block.moveDown();
      start = clock();
      block.draw();
    }
    hitbottom = !checkDown(block);

  }
  commitTetrimino(block);
}

bool Game::checkDown(Tetrimino block) {
  //checks if there is free space below tetrimino to fall
  bool spaceclear = true;
  for (int i = 0; i < 4; i++) {
    int row = block.getPosition('y',i);
    int col = block.getPosition('x',i);
    if ((well[col][row+1] != ' ') or (row >= 19)) spaceclear = false;
  }
  return spaceclear;
}

bool Game::checkRight(Tetrimino block) {
  //checks for free space to the right of tetrimino
  bool spaceclear = true;
  for (int i = 0; i < 4; i++) {
    int row = block.getPosition('y',i);
    int col = block.getPosition('x',i);
    if ((well[col+1][row] != ' ') or (col >= 9)) spaceclear = false;
  }
  return spaceclear;
}

bool Game::checkLeft(Tetrimino block) {
  //checks for free space to the left of tetrimino
  bool spaceclear = true;
  for (int i = 0; i < 4; i++) {
    int row = block.getPosition('y',i);
    int col = block.getPosition('x',i);
    if ((well[col-1][row] != ' ') or (col <= 0)) spaceclear = false;
  }
  return spaceclear;
}

bool Game::checkRotate(Tetrimino block) {
  //checks for free space enough to rotate tetrimino
  bool spaceclear = true;
  block.rotate();
  for (int i = 0; i < 4; i++) {
    if (block.getPosition('y',i) > 19) spaceclear = false;
    if (well[block.getPosition('x',i)][block.getPosition('y',i)] != ' ') spaceclear = false;
  }
  return spaceclear;
}

void Game::commitTetrimino(Tetrimino block) {
  //writes tetrimino position to well array
  char shape = block.getShape();
  for (int i = 0; i < 4; i++) {
    well[block.getPosition('x',i)][block.getPosition('y',i)] = shape;
  }
}

void Game::draw() {
  //Draws gameboard to the screen
  gfx_clear();
  drawUI();
  int well_x = 400;
  int well_y = 200;
  int wellcorner_x = 200;
  int wellcorner_y = 25;
  gfx_color(255,255,255);
  gfx_rectangle(wellcorner_x,wellcorner_y,well_y,well_x);
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 10; col++) {
      switch (well[col][row]) {
        case 'I':
          gfx_color(253,164,40); //orange
          gfx_fill_rectangle(wellcorner_x+20*col+1,wellcorner_y+20*row+1,18,18);
          break;
        case 'O':
          gfx_color(252,40,252); //magenta
          gfx_fill_rectangle(wellcorner_x+20*col+1,wellcorner_y+20*row+1,18,18);
          break;
        case 'T':
          gfx_color(45,255,254); //cyan
          gfx_fill_rectangle(wellcorner_x+20*col+1,wellcorner_y+20*row+1,18,18);
          break;
        case 'J':
          gfx_color(133,253,49); //lime
          gfx_fill_rectangle(wellcorner_x+20*col+1,wellcorner_y+20*row+1,18,18);
          break;
        case 'L':
          gfx_color(252,13,27); //red
          gfx_fill_rectangle(wellcorner_x+20*col+1,wellcorner_y+20*row+1,18,18);
          break;
        case 'S':
          gfx_color(255,253,56); //yellow
          gfx_fill_rectangle(wellcorner_x+20*col+1,wellcorner_y+20*row+1,18,18);
          break;
        case 'Z':
          gfx_color(11,36,251); //blue
          gfx_fill_rectangle(wellcorner_x+20*col+1,wellcorner_y+20*row+1,18,18);
          break;
      }
    }
  }
}

void Game::drawUI() {
  //Draws title, score, and instructions to the screen.
  int corner_x = 25, corner_y = 25;
  gfx_color(255,255,255);

  char font[] = "r24";
  char title[] = "TETRIS";
  corner_y += gfx_textpixelheight(title,font);
  gfx_changefont(font);
  gfx_text(corner_x,corner_y,title);

  font[1] = '1'; font[2] = '6';
  gfx_changefont(font);
  char levelmessage[11] = "Level: ";
  corner_y += gfx_textpixelheight(title,font)*2;
  sprintf(&levelmessage[7],"%u",score/10+1);
  gfx_text(corner_x, corner_y,levelmessage);

  corner_y += gfx_textpixelheight(title,font)*2;
  char font2[] = "7x14";
  gfx_changefont(font2);
  char instruction1[] = "A/D = left/right";
  gfx_text(corner_x,corner_y,instruction1);

  corner_y += gfx_textpixelheight(title,font2)*2;
  char instruction2[] = "W = spin";
  gfx_text(corner_x,corner_y,instruction2);

  corner_y += gfx_textpixelheight(title,font2)*2;
  char instruction3[] = "S = soft drop";
  gfx_text(corner_x,corner_y,instruction3);

  corner_y += gfx_textpixelheight(title,font2)*2;
  char instruction4[] = "Space = hard drop";
  gfx_text(corner_x,corner_y,instruction4);

  corner_y += gfx_textpixelheight(title,font2)*2;
  char instruction5[] = "ESC = exit";
  gfx_text(corner_x,corner_y,instruction5);
}
