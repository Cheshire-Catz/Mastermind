#ifndef SCORES_H
#define SCORES_H

#include "text.h"
#include "utils.h"

/*
  Structures
*/

typedef struct scores
{
  s_text* text;
  int     player;
  int     master;
} s_scores;

/*
  Prototypes
*/

s_scores* scores__init();

void scores__update(s_scores* fScores, bool fPlayerWon);

void scores__blit(s_surface* fScreen, s_scores* fScores);

void scores__free(s_scores* fScores);

#endif
