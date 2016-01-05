#ifndef CLUE_H
#define CLUE_H

#include "surface.h"
#include "text.h"

/*
  Structures
*/

struct clue
{
  struct text* text[TRY];
  int          color[TRY];
  int          position[TRY];
};

/*
  Prototypes
*/

struct clue* clue__init(SDL_Surface* fScreen);

void clue__new_game(struct clue* fClue);

void clue__update(struct clue* fClue, int fColor, int fPosition, int fTry);

void clue__blit(struct clue* fClue);

void clue__free(struct clue* fClue);

#endif
