#ifndef SURFACE_H
#define SURFACE_H

#include "utils.h"
#include "color.h"

/*
  In order to have test completely independent from SDL.
*/

#ifdef TEST

typedef struct surface
{
  e_color color;
} s_surface;

#else

#include <SDL/SDL.h>

typedef struct surface
{
  SDL_Surface* content;
  e_color      color;
} s_surface;

#endif

/*
  Prototypes
*/

s_surface* screen__init(e_color fColor);

void screen__flip(s_surface* fScreen);

s_surface* surface__init(int fWidth, int fHeight, e_color fColor);

void surface__update(s_surface* fSurface);

void surface__blit(s_surface* fScreen, s_surface* fSurface, s_pos fPos);

void surface__free(s_surface* fSurface);

#endif
