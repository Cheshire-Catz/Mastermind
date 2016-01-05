#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL_ttf.h>

#include "surface.h"
#include "canvas.h"
#include "color.h"

/*
  Constantes
*/

#define FONT "../font/Opificio-Serif-Bold.ttf"

/*
  Enumeration
*/

enum position {CENTER, UP_LEFT, UP_RIGHT};

/*
  Structures
*/

struct text
{
  TTF_Font*       font;
  int             size;
  struct surface* container;
};

/*
  Prototypes
*/

struct text* text__init(int fSize, struct surface* fSurface);

void text__blit(struct text* fText, char* fStr, enum position fTextPosition, SDL_Rect fSurfacePosition);

void text__free(struct text* fText);
  
#endif
