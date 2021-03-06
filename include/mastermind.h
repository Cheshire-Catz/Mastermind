#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "event.h"
#include "utils.h"
#include "window.h"

/*
  Structures
*/

typedef struct mastermind
{
  s_window* window;
  bool      stop;
  bool      win;
  int       try;
  e_color   target[4];
} s_mastermind;

/*
  Prototypes
*/

s_mastermind* mastermind__init(int fTry);

void mastermind__new_game(s_mastermind* fMastermind);

void mastermind__build_target(e_color* fTarget);

bool mastermind__add_answer(s_mastermind* fMastermind);

bool mastermind__remove_answer(s_mastermind* fMastermind);

bool mastermind__check_answer(s_mastermind* fMastermind);

void mastermind__play(s_mastermind* fMastermind);

bool mastermind__is_finished(s_mastermind* fMastermind);

void mastermind__free(s_mastermind* fMastermind);

#endif
