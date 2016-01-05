#ifndef COLOR_H
#define COLOR_H

#include <SDL/SDL.h>

/*
  Constantes
*/

#define NB_COLORS 9

/*
  Enumerations
*/

enum color {RED=0, BROWN, YELLOW, GREEN, BLUE, PURPLE, CYAN, PINK, ORANGE, WHITE, BLACK};

/*
  Prototypes
*/

SDL_Color color__value(enum color fColor);
  
#endif
