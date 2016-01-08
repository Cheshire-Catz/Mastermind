#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL_ttf.h>

#include "utils.h"
#include "surface.h"

/*
  Structures
*/

typedef struct text
{
  char       str[STRMAX];
  int        size;
  s_surface* container;
} s_text;

/*
  Prototypes
*/

s_text* text__init(int fSize, s_surface* fSurface);

void text__blit(s_surface* fScreen, s_text* fText, s_pos fPos);

void text__update(s_text* fText, char* fStr);

void text__free(s_text* fText);
  
#endif
