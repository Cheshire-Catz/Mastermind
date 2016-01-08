#ifndef CLUE_H
#define CLUE_H

#include "text.h"
#include "utils.h"
#include "surface.h"

/*
  Structures
*/

typedef struct clue
{
  s_text* text[TRY];
  int     color[TRY];
  int     position[TRY];
} s_clue;

/*
  Prototypes
*/

s_clue* clue__init();

void clue__new_game(s_clue* fClue);

void clue__update(s_clue* fClue, int fColor, int fPosition, int fTry);

void clue__blit(s_surface* fScreen, s_clue* fClue);

void clue__free(s_clue* fClue);

#endif
