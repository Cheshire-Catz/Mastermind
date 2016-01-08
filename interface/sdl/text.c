#include "../../include/text.h"

s_text* text__init(int fSize, s_surface* fSurface)
{
  s_text* _text = NULL;

  if((_text = malloc(sizeof(s_text))) == NULL)
    {
      printf("Error while allocating memory for text structures.\n");
      exit(-1);
    }

  strcpy(_text->str, "");
  _text->size      = fSize;
  _text->container = fSurface;

  return _text;
}

void text__blit(s_surface* fScreen, s_text* fText, s_pos fPos)
{
  surface__update(fText->container);

  TTF_Font* _font = NULL;

  if((_font = TTF_OpenFont(FONT, fText->size)) == NULL)
    {
      printf("Error while opening the font %s ! \n", FONT);
      exit(-1);
    }

  SDL_Surface* _content = TTF_RenderText_Solid(_font, fText->str, (SDL_Color){255, 255, 255});

  int _width = 0, _height = 0;
  TTF_SizeText(_font, fText->str, &_width, &_height);
  
  SDL_BlitSurface(_content, NULL, fText->container->content, &(SDL_Rect){(fText->container->content->w - _width) / 2., (fText->container->content->h - _height) / 2.});

  surface__blit(fScreen, fText->container, fPos);

  SDL_FreeSurface(_content);

  TTF_CloseFont(_font);
}

void text__update(s_text* fText, char* fStr)
{
  strcpy(fText->str, fStr);
}

void text__free(s_text* fText)
{
  if(fText != NULL)
    {
      if(fText->container != NULL)
        surface__free(fText->container);
      
      free(fText);
    }
}
