#ifndef  H_IG
#define H_IG
  #include <stdlib.h>
  #include <string.h>
  #include <stdio.h>
  #include <SDL/SDL.h>
  #include <SDL/SDL_image.h>
  #include "constante.h"
  #include "List.h"


  void printState(Tile grille[][8], int tour,List* capturedPiece[2],List* moves,SDL_Surface *screen, int** cp);
  Tuple getClick(SDL_Surface *screen);



#endif
