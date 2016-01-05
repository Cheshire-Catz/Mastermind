#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "surface.h"
#include "color.h"
#include "clue.h"

/*
  Structures
*/

struct board
{
  struct surface* answer[TARGET_SIZE][TRY];
  struct clue*    clue;
  int             index;
};

/*
  Prototypes
*/

struct board* board__init(SDL_Surface* fScreen);

void board__blit(struct board* fBoard);

void board__new_game(struct board* fBoard);

void board__add_answer(struct board* fBoard, enum color fColor, int fTry);

enum color board__remove_answer(struct board* fBoard, int fTry);

int board__check_position(struct board* fBoard, enum color* fTarget, int fTry);

int board__check_color(struct board* fBoard, enum color* fTarget, int fTry);

void board__update(struct board* fBoard, int fNbColors, int fNbPositions, int fTry);

bool board__is_full (struct board* fBoard);

bool board__is_empty(struct board* fBoard);

void board__free(struct board* fBoard);

int board__answer_size(struct board* fBoard);

void board__answer_random(struct board* fBoard, int fSize, int fTry);

#endif
