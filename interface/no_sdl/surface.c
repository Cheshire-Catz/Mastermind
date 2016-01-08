#include "../../include/surface.h"

s_surface* screen__init(e_color fColor)
{
  s_surface* _screen = malloc(sizeof(s_surface));
  
  _screen->color = fColor;

  return _screen;
}

void screen__flip(s_surface* fScreen)
{
  
}

s_surface* surface__init(int fWidth, int fHeight, e_color fColor)
{
  s_surface* _surface = malloc(sizeof(s_surface));

  _surface->color = fColor;

  return _surface;
}

void surface__update(s_surface* fSurface)
{
  
}

void surface__blit(s_surface* fScreen, s_surface* fSurface, s_pos fPos)
{ 

}

void surface__free(s_surface* fSurface)
{
  if(fSurface != NULL)
    {
      free(fSurface);
    }
}

