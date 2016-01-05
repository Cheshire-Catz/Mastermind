#include "color.h"

SDL_Color color__value(enum color fColor)
{
  SDL_Color _color;
  
  switch(fColor)
    {
    case WHITE:
      _color = (SDL_Color){255,255,255};
      break;
      
    case BLACK:
      _color = (SDL_Color){0,0,0};
      break;
      
    case RED:
      _color = (SDL_Color){255,0,0};
      break;
      
    case BROWN:
      _color = (SDL_Color){122,0,0};
      break;
      
    case YELLOW:
      _color = (SDL_Color){255,255,0};
      break;
      
    case GREEN:
      _color = (SDL_Color){0,255,0};
      break;
      
    case BLUE:
      _color = (SDL_Color){0,0,255};
      break;
      
    case PURPLE:
      _color = (SDL_Color){122,0,122};
      break;
      
    case CYAN:
      _color = (SDL_Color){0,255,255};
      break;
      
    case PINK:
      _color = (SDL_Color){255,0,255};
      break;
      
    case ORANGE:
      _color = (SDL_Color){255,165,0};
      break;
      
    default:
      _color = (SDL_Color){255,255,255};
      break;
    }

  return _color;
}
