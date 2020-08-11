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

  return EXIT_SUCCESS;
}
