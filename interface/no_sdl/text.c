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
