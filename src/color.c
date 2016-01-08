#include "../include/color.h"

s_rgb color__value(e_color fColor)
{
  s_rgb _color = {0,0,0};
  
  switch(fColor)
    {
    case WHITE:
      _color = (s_rgb){255,255,255};
      break;
      
    case BLACK:
      _color = (s_rgb){0,0,0};
      break;
      
    case RED:
      _color = (s_rgb){255,0,0};
      break;
      
    case BROWN:
      _color = (s_rgb){122,0,0};
      break;
      
    case YELLOW:
      _color = (s_rgb){255,255,0};
      break;
      
    case GREEN:
      _color = (s_rgb){0,255,0};
      break;
      
    case BLUE:
      _color = (s_rgb){0,0,255};
      break;
      
    case PURPLE:
      _color = (s_rgb){122,0,122};
      break;
      
    case CYAN:
      _color = (s_rgb){0,255,255};
      break;
      
    case PINK:
      _color = (s_rgb){255,0,255};
      break;
      
    case ORANGE:
      _color = (s_rgb){255,165,0};
      break;
      
    default:
      _color = (s_rgb){255,255,255};
      break;
    }

  return _color;
}

