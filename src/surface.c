#include "surface.h"

struct surface* surface__init(SDL_Surface* fScreen, int fWidth, int fHeight, enum color fColor)
{
  struct surface* _surface = malloc(sizeof(struct surface));

  _surface->screen    = fScreen;
  _surface->color     = fColor;
  
  _surface->content = SDL_CreateRGBSurface(SDL_HWSURFACE, fWidth, fHeight, 32, 0, 0, 0, 0);
  
  return _surface;
}

void surface__update(struct surface* fSurface)
{
  SDL_Color _color = color__value(fSurface->color);

  SDL_FillRect(fSurface->content, NULL, SDL_MapRGB(fSurface->screen->format, _color.r, _color.g, _color.b));
}

void surface__blit(struct surface* fSurface, SDL_Rect fPosition)
{ 
  SDL_BlitSurface(fSurface->content, NULL, fSurface->screen, &fPosition);
}

void surface__free(struct surface* fSurface)
{
  if(fSurface != NULL)
    {
      if(fSurface->content != NULL)
        SDL_FreeSurface(fSurface->content);

      free(fSurface);
    }
}
