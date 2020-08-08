#ifndef H_C
#define H_C

  #define VIDE     0
  #define PION     1
  #define CAVALIER 2
  #define TOUR     3
  #define FOU      4
  #define REINE    5
  #define ROI      6

  #define BLANC    7
  #define NOIR     -7

  typedef struct Tile Tile;
  struct Tile {
    int piece;
    int color;
  };

  typedef struct Tuple Tuple;
  struct Tuple {
    int x;
    int y;
  };

#endif
