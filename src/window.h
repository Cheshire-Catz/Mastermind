#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include "text.h"
#include "board.h"
#include "choice.h"
#include "scores.h"

/*
  Structures
*/

struct window
{
  SDL_Surface*    screen;
  struct scores*  scores;
  struct board*   board;
  struct choice*  choice;
};

/*
  Prototypes
*/

struct window* window__init(bool fDisplay);

void window__new_game(struct window* fWindow, bool fPlayerWon);

void window__display      (struct window* fWindow);

bool window__cursor_move  (struct window* fWindow, int fDir);

bool window__add_answer   (struct window* fWindow, int fTry);

bool window__remove_answer(struct window* fWindow, int fTry);

bool window__check_answer (struct window* fWindow, enum color* fTarget, int* fTry);

int window__answer_size(struct window* fWindow);

int window__targeted_color_stack(struct window* fWindow);

void window__answer_random(struct window* fWindow, int fSize, int fTry);

void window__free(struct window* fWindow);

#endif
