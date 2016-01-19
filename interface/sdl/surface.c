#include "../../include/surface.h"

s_surface* screen__init(e_color fColor)
{
  s_surface* _screen = malloc(sizeof(s_surface));

  _screen->content = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

  SDL_WM_SetCaption("Mastermind", NULL);
  
  _screen->color = fColor;

  return _screen;
}

void screen__flip(s_surface* fScreen)
{
  SDL_Flip(fScreen->content);
}

s_surface* surface__init(int fWidth, int fHeight, e_color fColor)
{
  s_surface* _surface = malloc(sizeof(s_surface));

  _surface->color = fColor;
  
  _surface->content = SDL_CreateRGBSurface(SDL_HWSURFACE, fWidth, fHeight, 32, 0, 0, 0, 0);
  
  return _surface;
}

void surface__update(s_surface* fSurface)
{
  s_rgb _color = color__value(fSurface->color);

  SDL_FillRect(fSurface->content, NULL, SDL_MapRGB(fSurface->content->format, _color.r, _color.g, _color.b));
}

void surface__blit(s_surface* fScreen, s_surface* fSurface, s_pos fPos)
{ 
  SDL_BlitSurface(fSurface->content, NULL, fScreen->content, &(SDL_Rect){fPos.x, fPos.y});
}

void surface__free(s_surface* fSurface)
{
  if(fSurface != NULL)
    {
      if(fSurface->content != NULL)
        SDL_FreeSurface(fSurface->content);

      free(fSurface);
    }
}
