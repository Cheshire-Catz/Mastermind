#ifndef COLOR_H
#define COLOR_H

/*
  Constantes
*/

#define NB_COLORS 9

/*
  Enumerations
*/

typedef enum color {RED=0, BROWN, YELLOW, GREEN, BLUE, PURPLE, CYAN, PINK, ORANGE, WHITE, BLACK} e_color;

/*
  Structures
*/

typedef struct rgb
{
  char r;
  char g;
  char b;
} s_rgb;

/*
  Prototypes
*/

s_rgb color__value(e_color fColor);

#endif
