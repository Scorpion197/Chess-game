#ifndef H_G
#define H_G

  #include <stdio.h>
  #include <stdlib.h>

  #include "constante.h"
  #include "game_interface.h"
  #include "List.h"

  void initGame(SDL_Surface *screen);
  int initGrille(Tile Grille[][8]);
  void actualiseState(Tile grille[][8],int tour, List* moves, List* capturedPiece[2], Tuple fromCoord,Tuple destCoord);

  int validBaseInput(Tile grille[][8], int tour, Tuple fromCoord);
  int validTopInput(Tile grille[][8], int tour, Tuple fromCoord, Tuple destCoord);


  int** genCoupPossible(Tile grille[][8], Tuple coord, int tour);
  int chikhMat(Tile grille[8][8], int tour);

  void freeMat(int** Mat);

#endif
