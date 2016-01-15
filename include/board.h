#ifndef BOARD_H
#define BOARD_H

#include "clue.h"
#include "color.h"
#include "utils.h"
#include "surface.h"

/*
  Structures
*/

typedef struct board
{
  s_surface* answer[TARGET_SIZE][TRY];
  s_clue*    clue;
  int        index;
} s_board;

/*
  Prototypes
*/

s_board* board__init();

void board__blit(s_surface* fScreen, s_board* fBoard);

void board__new_game(s_board* fBoard);

void board__add_answer(s_board* fBoard, e_color fColor, int fTry);

e_color board__remove_answer(s_board* fBoard, int fTry);

int board__check_position(s_board* fBoard, e_color* fTarget, int fTry);

int board__check_color(s_board* fBoard, e_color* fTarget, int fTry);

void board__update(s_board* fBoard, int fNbColors, int fNbPositions, int fTry);

bool board__is_full (s_board* fBoard);

bool board__is_empty(s_board* fBoard);

void board__free(s_board* fBoard);

#endif
