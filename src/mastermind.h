#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "canvas.h"
#include "window.h"

/*
  Structures
*/

struct mastermind
{
  struct window* window;
  SDL_Event      event;
  bool           stop;
  bool           win;
  int            try;
  enum color     target[4];
};

/*
  Prototypes
*/

struct mastermind* mastermind__init(bool fDisplay);

void mastermind__new_game(struct mastermind* fMastermind);

void mastermind__build_target(enum color* fTarget);

void mastermind__play(struct mastermind* fMastermind);

bool mastermind__is_finished(struct mastermind* fMastermind);

void mastermind__free(struct mastermind* fMastermind);

#endif
