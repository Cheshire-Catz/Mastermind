#include "text.h"

struct text* text__init(int fSize, struct surface* fSurface)
{
  struct text* _text = malloc(sizeof(struct text));

  _text->font      = NULL;
  _text->size      = fSize;
  _text->container = fSurface;

  return _text;
}

void text__load_font(struct text* fText)
{
  if((fText->font = TTF_OpenFont(FONT, fText->size)) == NULL)
    {
      printf("Error while opening the font %s ! \n", FONT);
      exit(-1);
    }
}

void text__blit(struct text* fText, char* fStr, enum position fTextPosition, SDL_Rect fSurfacePosition)
{
  surface__update(fText->container);

  if(fText->font == NULL)
    text__load_font(fText);  
  
  SDL_Surface* _content = TTF_RenderText_Solid(fText->font, fStr, color__value(WHITE));

  int _width = 0, _height = 0;
  TTF_SizeText(fText->font, fStr, &_width, &_height);
  
  SDL_Rect _position = {0,0};
  
  switch(fTextPosition)
    {
    case CENTER:
      _position = (SDL_Rect){(fText->container->content->w - _width) / 2., (fText->container->content->h - _height) / 2.};
      break;

    case UP_LEFT:
      _position = (SDL_Rect){fText->container->content->w / 30, fText->container->content->h / 30};
      break;
      
    case UP_RIGHT:
      _position = (SDL_Rect){fText->container->content->w - _width - fText->container->content->w / 30, fText->container->content->h / 30};
      break;

    default:
      break;
    }
  
  SDL_BlitSurface(_content, NULL, fText->container->content, &_position);

  surface__blit(fText->container, fSurfacePosition);

  SDL_FreeSurface(_content);
}

void text__free(struct text* fText)
{
  if(fText != NULL)
    {
      if(fText->font != NULL)
        TTF_CloseFont(fText->font);
      
      if(fText->container != NULL)
        surface__free(fText->container);
      
      free(fText);
    }
}
