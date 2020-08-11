#include "game.h"

void initGame(SDL_Surface *screen){
  int gameover = 0,
      tour = BLANC;

  Tile grille[8][8];
  List* capturedPiece[2] = {NULL, NULL};
  List* moves = NULL;

  initGrille(grille);

  while ( !gameover ) {

    printState(grille, tour, capturedPiece, moves, screen, NULL);

    int moveChoosed = 0;

    Tuple posClick = {-1 , -1},
          fromCoord = {-1 , -1},
          destCoord = {-1 , -1};

    while ( !moveChoosed ) {
      posClick = getClick(screen);

      printf("%d  %d\n", posClick.x, posClick.y);

      if ( posClick.x == -1 )// If the user decides to close the game window
      {
        printf("Sortie\n");
        exit(0);
      }

      else if ( validBaseInput(grille, tour, posClick) )
      {
        int** listCoupPossible = genCoupPossible(grille, posClick, tour);
        fromCoord = posClick;
        printState(grille, tour, capturedPiece, moves, screen, listCoupPossible);//listCoupPossible);
        printf("allocated\n");
        freeMat(listCoupPossible);
      }
      else if ( validTopInput(grille, tour, fromCoord, posClick) )
      {
        destCoord = posClick;
        moveChoosed = 1;
      }

    }

    actualiseState(grille, tour, moves, capturedPiece, fromCoord, destCoord);

    // gameover = chikhMat(grille, tour);

    tour = -tour;


  }

}

int initGrille(Tile grille[][8]){


  for (size_t i = 0; i < 8; i++)
    for (size_t j = 0; j < 8; j++)
    {
      grille[i][j].piece = VIDE;
      grille[i][j].color = VIDE;
    }



  for (int i = 0; i < 8; i++) {
    grille[6][i].piece = PION;
    grille[1][i].piece = PION;

    grille[6][i].color = NOIR;
    grille[7][i].color = NOIR;
    grille[1][i].color = BLANC;
    grille[0][i].color = BLANC;
  }

  grille[7][0].piece = TOUR;
  grille[7][1].piece = CAVALIER;
  grille[7][2].piece = FOU;
  grille[7][3].piece = ROI;
  grille[7][4].piece = REINE;
  grille[7][5].piece = FOU;
  grille[7][6].piece = CAVALIER;
  grille[7][7].piece = TOUR;

  grille[0][0].piece = TOUR;
  grille[0][1].piece = CAVALIER;
  grille[0][2].piece = FOU;
  grille[0][3].piece = ROI;
  grille[0][4].piece = REINE;
  grille[0][5].piece = FOU;
  grille[0][6].piece = CAVALIER;
  grille[0][7].piece = TOUR;
}

int validBaseInput(Tile grille[][8],int tour, Tuple currentPos){

    if ((grille[currentPos.x][currentPos.y].color == tour) && (grille[currentPos.x][currentPos.y].piece != VIDE ))
        return 1;
    else
        return 0;
}

int validTopInput(Tile grille[][8], int tour, Tuple fromCoord, Tuple destCoord){
  if (fromCoord.x == -1)
  {
    return 0;
  }
  else
  {
    int** coupPossible = genCoupPossible(grille, fromCoord, tour);

    int valid = ( coupPossible[destCoord.x][destCoord.y] == 1);
    printf("valid %d %d %d\n", fromCoord.x, fromCoord.y, tour );

    printf("\n");
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {
        printf("%d  ", coupPossible[i][j]);
      }
      printf("\n");
    }

    freeMat(coupPossible);

    return valid;
  }
}

int** genCoupPossible(Tile grille[][8], Tuple coord, int tour){

  int** coupPossible = malloc(8*sizeof(int*));
  for (int i = 0; i < 8; i++)
    coupPossible[i] = malloc(8*sizeof(int));

  /* For testing purposes only */
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      coupPossible[i][j] = 0;


  //PAWN
  //==============================================================
  if ( grille[coord.x][coord.y].piece == PION) {
    int pasclassique = 0; // Si on peut fair un pas classique, on met cette variable a 1

    //CLASSICAL MOVE
    if ( grille[coord.x+1][coord.y].piece == VIDE && tour == BLANC){
      coupPossible[coord.x+1][coord.y] = 1;
      pasclassique = 1;
    }

    else if ( grille[coord.x-1][coord.y].piece == VIDE && tour == NOIR){
      coupPossible[coord.x-1][coord.y] = 1;
      pasclassique = 1;
    }

    //FIRST MOVE
    if ( pasclassique && (( coord.x == 1 && tour == BLANC ) || ( coord.x == 6 && tour == NOIR )))
    {

      if ( grille[coord.x+2][coord.y].piece == VIDE && tour == BLANC)
        coupPossible[coord.x+2][coord.y] = 1;

      else if ( grille[coord.x-2][coord.y].piece == VIDE && tour == NOIR)
        coupPossible[coord.x-2][coord.y] = 1;

    }

    //TAKING OPPONENT'S PIECE
    if ( coord.y != 0 ) {
      if ( grille[coord.x+1][coord.y-1].color == -tour && tour == BLANC)
        coupPossible[coord.x+1][coord.y-1] = 1;
      else if ( grille[coord.x-1][coord.y-1].color == -tour && tour == NOIR)
        coupPossible[coord.x-1][coord.y-1] = 1;
    }
    if ( coord.y != 7 ) {
      if ( grille[coord.x+1][coord.y+1].color == -tour && tour == BLANC)
        coupPossible[coord.x+1][coord.y+1] = 1;
      else if ( grille[coord.x-1][coord.y+1].color == -tour && tour == NOIR)
        coupPossible[coord.x-1][coord.y+1] = 1;
    }

  }
  //ROOK OR QUEEN
  //==============================================================
   if ( grille[coord.x][coord.y].piece == TOUR || grille[coord.x][coord.y].piece == REINE) {
      int i;
      i = 1;

      while ( coord.y+i < 8 && grille[coord.x][coord.y+i].color != tour ) {
        coupPossible[coord.x][coord.y+i] = 1;
        if (grille[coord.x][coord.y+i].color == -tour)
          break;
        i++;
      }

      i = 1;
      while (  coord.y-i >= 0 && grille[coord.x][coord.y-i].color != tour) {
        coupPossible[coord.x][coord.y-i] = 1;
        if (grille[coord.x][coord.y-i].color == -tour)
          break;
        i++;
      }

      i = 1;
      while ( coord.x+i < 8 && grille[coord.x+i][coord.y].color != tour) {
        coupPossible[coord.x+i][coord.y] = 1;
        if (grille[coord.x+i][coord.y].color == -tour)
          break;
        i++;
      }

      i = 1;
      while ( coord.x-i >= 0 && grille[coord.x-i][coord.y].color != tour  ) {
        coupPossible[coord.x-i][coord.y] = 1;

        if (grille[coord.x-i][coord.y].color == -tour)
          break;
        i++;
      }
  }
  //BISHOP OR QUEEN
  //==============================================================
   if ( grille[coord.x][coord.y].piece == FOU || grille[coord.x][coord.y].piece == REINE) {
      int i;
      i = 1;

      while ( coord.y+i < 8  &&  coord.x+i < 8 && grille[coord.x+i][coord.y+i].color != tour ) {
        coupPossible[coord.x+i][coord.y+i] = 1;
        if (grille[coord.x+i][coord.y+i].color == -tour)
          break;
        i++;
      }

      i = 1;
      while ( coord.y-i >= 0  &&  coord.x+i < 8 && grille[coord.x+i][coord.y-i].color != tour ) {
        coupPossible[coord.x+i][coord.y-i] = 1;
        if (grille[coord.x+i][coord.y-i].color == -tour)
          break;
        i++;
      }

      i = 1;
      while ( coord.y+i < 8  &&  coord.x-i >= 0 && grille[coord.x-i][coord.y+i].color != tour ) {
        coupPossible[coord.x-i][coord.y+i] = 1;
        if (grille[coord.x-i][coord.y+i].color == -tour)
          break;
        i++;
      }

      i = 1;
      while ( coord.y-i >= 0  &&  coord.x-i >= 0 && grille[coord.x-i][coord.y-i].color != tour ) {
        coupPossible[coord.x-i][coord.y-i] = 1;
        if (grille[coord.x-i][coord.y-i].color == -tour)
          break;
        i++;
      }
  }
  //KNIGHT
  else if ( grille[coord.x][coord.y].piece == CAVALIER){

          // ONE FORWARD LEFT DIAGONAL STEP AND ANOTHER STEP TO THE LEFT
          if ((coord.x > 0 && coord.y > 1) && (grille[coord.x -1][coord.y -2].color != tour) )
              coupPossible[coord.x -1][coord.y - 2] = 1;

          // ONE FORWARD RIGHT DIAGONAL STEP AND ANOTHER STEP TO THE RIGHT
          if ((coord.x > 0 && coord.y < 6) && (grille[coord.x -1][coord.y +2].color != tour) )
              coupPossible[coord.x -1][coord.y +2] = 1;

          // ONE BACKWARD LEFT DIAGONAL STEP AND ANOTHER ONE TO THE LEFT
          if ((coord.x < 7 && coord.y > 1) && (grille[coord.x +1][coord.y -2].color != tour) )
              coupPossible[coord.x +1][coord.y -2] = 1;

          // ONE BACKWARD RIGHT DIAGONAL STEP AND ANOTHER STEP TO THE RIGHT
          if ((coord.x < 7 && coord.y < 6) && (grille[coord.x +1][coord.y +2].color != tour) )
              coupPossible[coord.x +1][coord.y +2] = 1;

          // ONE FORWARD LEFT DIAGONAL STEP AND ANOTHER FORWARD ONE
          if ((coord.x > 1 && coord.y > 0) && (grille[coord.x -2][coord.y -1].color != tour) )
              coupPossible[coord.x -2][coord.y -1] = 1;

          // ONE FORWARD RIGHT DIAGONAL STEP AND ANOTHER FORWARD ONE
          if ((coord.x > 1 && coord.y < 7) && (grille[coord.x -2][coord.y +1].color != tour) )
              coupPossible[coord.x -2][coord.y +1] = 1;

          // ONE BACKWARD DIAGONAL LEFT MOVE AND ANOTHER FORWARD MOVE
          if ((coord.x < 6 && coord.y > 0  && (grille[coord.x +2][coord.y -1].color != tour) ))
              coupPossible[coord.x +2][coord.y -1] = 1;

          // ONE BACKWARD DIAGONAL RIGHT MOVE AND ANOTHER BACKWARD ONE
          if ((coord.x < 6 && coord.y < 7) && (grille[coord.x +2][coord.y +1].color != tour) )
              coupPossible[coord.x +2][coord.y +1] = 1;

  }
  // KING
  if ( grille[coord.x][coord.y].piece == ROI){
  // FORWARD STEP
        if ((grille[coord.x + 1][coord.y].color != tour) && (coord.x < 7 ))
            coupPossible[coord.x + 1][coord.y] = 1;

        // BACKWARD STEP
        if ((grille[coord.x -1][coord.y].color != tour) && (coord.x > 0))
            coupPossible[coord.x -1][coord.y] = 1;

        // MOVE TO THE RIGHT
        if ((grille[coord.x][coord.y + 1].color != tour) && (coord.y < 7))
            coupPossible[coord.x][coord.y + 1] = 1;

        // MOVE TO THE LEFT
        if ((grille[coord.x][coord.y - 1].color != tour) && (coord.y > 0))
            coupPossible[coord.x][coord.y - 1] = 1;

        // FORWARD LEFT DIAGONAL MOVE
        if ((grille[coord.x - 1][coord.y - 1].color != tour) && (coord.x > 0 && coord.y > 0))
            coupPossible[coord.x - 1][coord.y - 1] = 1;

        // FORWARD RIGHT DIAGONAL MOVE
        if ((grille[coord.x -1][coord.y + 1].color != tour) && (coord.x > 0 && coord.y < 7))
            coupPossible[coord.x - 1][coord.y + 1] =1;

        // BACKWARD RIGHT DIAGONAL MOVE
        if ((grille[coord.x + 1][coord.y + 1].color != tour ) && (coord.x < 7 && coord.y < 7))
            coupPossible[coord.x +1][coord.y +1] = 1;

        // BACKWARD LEFT DIAGONAL MOVE
         if ((grille[coord.x +1][coord.y -1].color != tour) && (coord.x < 7 && coord.y > 0))
            coupPossible[coord.x +1][coord.y -1] =1;

    }

  // coupPossible[coord.x][coord.y] = 2;

  return coupPossible;
}

void actualiseState(Tile grille[][8],int tour,List* moves, List* capturedPiece[2], Tuple fromCoord,Tuple destCoord){

  int i, j;
  //REFRESH CAPTURED PIECES
  //============================================================================
      if (grille[destCoord.x][destCoord.y].piece != VIDE)
         insertion_list(&capturedPiece[tour], &grille[destCoord.x][destCoord.y].piece, sizeof(int));
  //============================================================================

  //============================================================================
      char movement[4];
      movement[0] = fromCoord.x + 65;//On est traduit en char
      movement[1] = fromCoord.y + 49;//Sachant que les coords y seront des nombres
      movement[2] = destCoord.x + 65;//et le coords x seront des chiffrs
      movement[3] = destCoord.y + 49;
  //============================================================================

  //REFRESH THE GRID
  //============================================================================
  grille[destCoord.x][destCoord.y].piece = grille[fromCoord.x][fromCoord.y].piece;
  grille[fromCoord.x][fromCoord.y].piece = VIDE;

  grille[destCoord.x][destCoord.y].color = tour;
  grille[fromCoord.x][fromCoord.y].color = VIDE;
  //============================================================================ 
}

int chikhMat(Tile grille[8][8], int tour){
  Tuple posRoi = {-1, -1};
  int i = 0, j = 0;
  int echec = 1;


  //SEARCH OPPONENT'S KING POSITION
  while ( i < 8 && posRoi.x == -1) {
    j = 0;
    while ( j < 8 && posRoi.x == -1) {

      if (grille[i][j].piece == ROI && grille[i][j].color != tour){//note: color
        posRoi.x = i;
        posRoi.y = j;
      }
      j++;
    }
    i++;
  }

  int** coupPossible = genCoupPossible(grille, posRoi, tour);

  i = 0; j = 0;
  while (i < 8 && echec)
  {
    while (j < 8 && echec)
    {
      if (coupPossible[i][j] == 1)// IF HE HAS A POSSIBLE MOVE
        echec = 0;

      j++;
    }
    i++;
  }

  return echec;
}

void freeMat(int** Mat) {
  for (int i = 0; i < 8; i++)
    free(Mat[i]);

  free(Mat);
}
