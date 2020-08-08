#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constante.h"
#include "game.h"



int main(int argc, char const *argv[]) {

  SDL_Surface *ecran = NULL, *square = NULL;
  Tile grille[8][8];

  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Chess game ", NULL);

  ecran = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

  if (ecran == NULL)
  {
      fprintf(stderr, "Erreur d'initialisation SDL %s\n",SDL_GetError());
      exit(EXIT_FAILURE);
  }

  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  initGame(ecran);
  
  SDL_Quit();


/*
  Tile grille[8][8];
  for (size_t i = 0; i < 8; i++)
    for (size_t j = 0; j < 8; j++)
    {
      grille[i][j].piece = VIDE;
      grille[i][j].color = VIDE;
    }

  grille[0][0].piece = PION;
  grille[0][0].color = NOIR;

  grille[1][1].piece = PION;
  grille[1][1].color = BLANC;


  int** a = genCoupPossible(grille, (Tuple){0, 0}, NOIR);
  int** b = genCoupPossible(grille, (Tuple){1, 1}, BLANC);

  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      printf("%d  ", a[j][i]);
    }
    printf("\n");
  }

  printf("\n");
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      printf("%d  ", b[j][i]);
    }
    printf("\n");
  }
*/
  printf("fin \n");
  return EXIT_SUCCESS;
}
