#ifndef WINDOW_H
#define WINDOW_H

#include "utils.h"
#include "board.h"
#include "choice.h"
#include "scores.h"
#include "surface.h"

/*
  Structures
*/

typedef struct window
{
  s_surface* screen;
  s_scores*  scores;
  s_board*   board;
  s_choice*  choice;
} s_window;

/*
  Prototypes
*/

s_window* window__init(bool fDisplay);

void window__new_game(s_window* fWindow, bool fPlayerWon);

void window__display      (s_window* fWindow);

bool window__cursor_move  (s_window* fWindow, int fDir);

bool window__add_answer   (s_window* fWindow, int fTry);

bool window__remove_answer(s_window* fWindow, int fTry);

bool window__check_answer (s_window* fWindow, e_color* fTarget, int* fTry);

int window__answer_size(s_window* fWindow);

int window__targeted_color_stack(s_window* fWindow);

void window__answer_random(s_window* fWindow, int fSize, int fTry);

void window__free(s_window* fWindow);

#endif
