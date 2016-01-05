#ifndef SCORES_H
#define SCORES_H

#include <stdbool.h>

#include "text.h"
#include "canvas.h"

/*
  Structures
*/

struct scores
{
  struct text* text;
  int          player;
  int          master;
};

/*
  Prototypes
*/

struct scores* scores__init(SDL_Surface* fScreen);

void scores__update(struct scores* fScores, bool fPlayerWon);

void scores__blit(struct scores* fScores);

void scores__free(struct scores* fScores);

#endif
