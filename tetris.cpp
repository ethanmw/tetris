//Ethan Williams, final project: Tetris
//final.cpp
#include<cstdlib>
#include <cstdio>
#include <ctime>
#include "Game.h"
#include "gfxnew.h"

void endgame(int score);

int main() {
  gfx_open(600,450,"Tetris");
  srand(time(NULL));
  Game tetris;
  int score = tetris.play();
  endgame(score);
}

void endgame(int score) {
  //Displays end-of-game score and exit messages
  gfx_clear();
  char font[] = "r24";
  char title[] = "TETRIS";
  int x = 200;
  int y = 25+gfx_textpixelheight(title,font);
  gfx_changefont(font);
  gfx_text(x,y,title);
  y += 2*gfx_textpixelheight(title,font);
  char font2[] = "r16";
  gfx_changefont(font2);
  char scoremessage[19] = "Your score was ";
  sprintf(&scoremessage[15],"%u",score);
  gfx_text(x,y,scoremessage);
  char font3[] = "7x14";
  char prompt[] = "Press esc or q to quit";
  y += 2*gfx_textpixelheight(title,font2);
  gfx_changefont(font3);
  gfx_text(x,y,prompt);

  char input = 0;
  while ((input != 'q') && (input != 27)) {
    input = gfx_wait();
  }
}
