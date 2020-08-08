#include "game_interface.h"

void printState(Tile grille[][8], int tour,List* capturedPiece[2],List* moves,SDL_Surface *screen, int** coupPossible)
{

    SDL_Surface *square = NULL, *pionNOIR = NULL, *pionBLANC = NULL, *tourNOIRE = NULL, *tourBLANCHE = NULL, *fouNOIR = NULL,
    *fouBLANCH = NULL, *reineNOIRE = NULL, *reineBLANCH = NULL, *roiNOIR = NULL, *roiBLANCH = NULL, *cavalierNOIR = NULL,
    *cavalierBLANCH = NULL;
    SDL_Surface *squares[8] = {NULL};
    SDL_Rect position;
    int board[8][8] = {0, 1, 0, 1, 0, 1, 0, 1,
                       1, 0, 1, 0, 1, 0, 1, 0,
                       0, 1, 0, 1, 0, 1, 0, 1,
                       1, 0, 1, 0, 1, 0, 1, 0,
                       0, 1, 0, 1, 0, 1, 0, 1,
                       1, 0, 1, 0, 1, 0, 1, 0,
                       0, 1, 0, 1, 0, 1, 0, 1,
                       1, 0, 1, 0, 1, 0, 1, 0};
    int i, j;

    position.x = 0;
    position.y = 0;

    for ( i = 0 ; i < 8; i++)
        squares[i] = SDL_CreateRGBSurface( SDL_HWSURFACE,100, 100, 32, 0, 0, 0, 0);


    for ( i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            position.x = j * 100;

            if (board[i][j] == 0)
                SDL_FillRect(squares[i], NULL, SDL_MapRGB(squares[i]->format,204, 102, 0)); /* White squares */

            else
                SDL_FillRect(squares[i], NULL, SDL_MapRGB(squares[i]->format,255, 178, 102)); /* black squares */

            SDL_BlitSurface(squares[i], NULL, screen, &position);


        }
        position.y = position.y + 100;
    }

    //Les coupPossible
    if (coupPossible != NULL) {

      SDL_Surface *rectangle = NULL;
      rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, 32, 0, 0, 0, 0);

      for ( i = 0; i < 8; i++)
          {
              for ( j = 0; j < 8; j++)
              {

                  if (coupPossible[i][j] == 1)
                      SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 0, 204, 0));
                  else if (coupPossible[i][j] == 2)
                      SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 190, 0, 0));

                  position.x = j * 100;
                  position.y = i * 100;

                  if ( coupPossible[i][j] != 0 )
                    SDL_BlitSurface(rectangle, NULL, screen, &position);

              }
          }
    }

    //===============================

    pionBLANC = IMG_Load("assets/pionBLANC.png");
    pionNOIR = IMG_Load("assets/pionNOIR.png");

    tourBLANCHE = IMG_Load("assets/tourBLANC.png");
    tourNOIRE = IMG_Load("assets/tourNOIR.png");

    reineBLANCH = IMG_Load("assets/reineBLANC.png");
    reineNOIRE = IMG_Load("assets/reineNOIR.png");

    roiBLANCH = IMG_Load("assets/roiBLANC.png");
    roiNOIR = IMG_Load("assets/roiNOIR.png");

    fouBLANCH = IMG_Load("assets/fouBLANC.png");
    fouNOIR = IMG_Load("assets/fouNOIR.png");

    cavalierBLANCH = IMG_Load("assets/cavalierBLANC.png");
    cavalierNOIR = IMG_Load("assets/cavalierNOIR.png");


    for (i = 0; i < 8; i++)
    {
        for ( j = 0; j < 8; j++)
        {
            position.x = j * 100;
            position.y = i * 100;

            if (grille[i][j].piece == PION)
            {
                if (grille[i][j].color == NOIR)
                    SDL_BlitSurface(pionNOIR, NULL, screen, &position);
                else
                    SDL_BlitSurface(pionBLANC, NULL, screen, &position);
            }

            if (grille[i][j].piece == TOUR)
            {
                if (grille[i][j].color == NOIR)
                    SDL_BlitSurface(tourNOIRE, NULL, screen, &position);
                else
                    SDL_BlitSurface(tourBLANCHE, NULL, screen, &position);
            }

            if (grille[i][j].piece == FOU)
            {
                if (grille[i][j].color == NOIR)
                    SDL_BlitSurface(fouNOIR, NULL, screen, &position);
                else
                    SDL_BlitSurface(fouBLANCH, NULL, screen, &position);
            }

            if (grille[i][j].piece == REINE)
            {
                if (grille[i][j].color == NOIR)
                    SDL_BlitSurface(reineNOIRE, NULL, screen, &position);
                else
                    SDL_BlitSurface(reineBLANCH, NULL, screen, &position);
            }

            if (grille[i][j].piece == CAVALIER)
            {
                if (grille[i][j].color == NOIR)
                    SDL_BlitSurface(cavalierNOIR, NULL, screen, &position);
                else
                    SDL_BlitSurface(cavalierBLANCH, NULL, screen, &position);
            }

            if (grille[i][j].piece == ROI)
            {
                if (grille[i][j].color == NOIR)
                    SDL_BlitSurface(roiNOIR, NULL, screen, &position);
                else
                    SDL_BlitSurface(roiBLANCH, NULL, screen, &position);
            }

        }
    }

    SDL_Flip(screen);
}

Tuple getClick(SDL_Surface *screen)
{

    Tuple positions;
    SDL_Event event;
    int continuer = 1;

    while (continuer)
    {

        SDL_Flip(screen);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                positions.x = -1;
                positions.y = -1;
                return positions;


            case SDL_MOUSEBUTTONDOWN:
                positions.x = event.button.y;
                positions.y = event.button.x;
                if ((positions.x / 100 < 8) && (positions.y / 100 < 8))
                 {
                     positions.x = positions.x / 100;
                     positions.y = positions.y / 100;
                     return positions;

                 }

                break;
        }
    }


}
