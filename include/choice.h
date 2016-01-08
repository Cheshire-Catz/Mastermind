#ifndef CHOICE_H
#define CHOICE_H

#include "text.h"
#include "utils.h"
#include "surface.h"

/*
  Constantes
*/

#define INIT_STACK 6

/*
  Structures
*/

typedef struct choice
{
  s_text*    text[NB_COLORS];
  e_color    color[NB_COLORS];
  int        stack[NB_COLORS];
  SDL_Rect   position[NB_COLORS];
  s_surface* cursor;
  int        index;
} s_choice;


/*
  Prototypes
*/

s_choice* choice__init();

void choice__new_game(s_choice* fChoice);

void choice__blit(s_surface* fScreen, s_choice* fChoice);

bool choice__cursor_move(s_choice* fChoice, int fDir);

e_color choice__pick_color(s_choice* fChoice);

void choice__depick_color(s_choice* fChoice, e_color fColor);

bool choice__is_available(s_choice* fChoice);

int choice__targeted_color_stack(s_choice* fChoice);

void choice__free(s_choice* fChoice);

#endif
