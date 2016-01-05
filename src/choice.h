#ifndef CHOICE_H
#define CHOICE_H

#include <stdbool.h>

#include "surface.h"
#include "text.h"
#include "canvas.h"

/*
  Constantes
*/

#define INIT_STACK 6

/*
  Structures
*/

struct choice
{
  struct text*    text[NB_COLORS];
  enum color      color[NB_COLORS];
  int             stack[NB_COLORS];
  SDL_Rect        position[NB_COLORS];
  struct surface* cursor;
  int             index;
};


/*
  Prototypes
*/

struct choice* choice__init(SDL_Surface* fScreen);

void choice__new_game(struct choice* fChoice);

void choice__blit(struct choice* fChoice);

bool choice__cursor_move(struct choice* fChoice, int fDir);

enum color choice__pick_color(struct choice* fChoice);

void choice__depick_color(struct choice* fChoice, enum color fColor);

bool choice__is_available(struct choice* fChoice);

int choice__targeted_color_stack(struct choice* fChoice);

void choice__free(struct choice* fChoice);

#endif
