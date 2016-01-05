#include "clue.h"

struct clue* clue__init(SDL_Surface* fScreen)
{
  struct clue* _clue = malloc(sizeof(struct clue));

  for(int i=0; i<TRY; i++)
    {
      _clue->color[i] = 0;
      _clue->position[i] = 0;
      _clue->text[i] = text__init(CLUE_SIZE, surface__init(fScreen, ANSWER_SIZE, CLUE_SIZE, BLACK));
    }

  return _clue;
}

void clue__new_game(struct clue* fClue)
{
  for(int i=0; i<TRY; i++)
    {
      fClue->color[i] = 0;
      fClue->position[i] = 0;
    }
}

void clue__update(struct clue* fClue, int fColor, int fPosition, int fTry)
{
  fClue->color[fTry] = fColor;
  fClue->position[fTry] = fPosition;
}

void clue__blit(struct clue* fClue)
{
  char _str[STRMAX];

  for(int i=0; i<TRY; i++)
    {
      sprintf(_str, "%d:%d", fClue->position[i], fClue->color[i]);
      text__blit(fClue->text[i], _str, CENTER, (SDL_Rect){CLUE_X(i), CLUE_Y});
    }
}

void clue__free(struct clue* fClue)
{
  if(fClue != NULL)
    {
      for(int i=0; i<TRY; i++)
        {
          if(fClue->text[i] != NULL)
            text__free(fClue->text[i]);
        }
      
      free(fClue);
    }
}
