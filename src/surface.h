#ifndef SURFACE_H
#define SURFACE_H

#include "color.h"

/*
  Structures
*/

struct surface
{
  SDL_Surface* screen;
  SDL_Surface* content;
  enum color   color;
};

/*
  Prototypes
*/

struct surface* surface__init(SDL_Surface* fScreen, int fWidth, int fHeight, enum color fColor);

void surface__update(struct surface* fSurface);

void surface__blit(struct surface* fSurface, SDL_Rect fPosition);

void surface__free(struct surface* fSurface);

#endif
