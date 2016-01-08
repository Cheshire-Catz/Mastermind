#include "../include/clue.h"

s_clue* clue__init()
{
  s_clue* _clue = malloc(sizeof(s_clue));

  for(int i=0; i<TRY; i++)
    {
      _clue->color[i] = 0;
      _clue->position[i] = 0;
      _clue->text[i] = text__init(CLUE_SIZE, surface__init(ANSWER_SIZE, CLUE_SIZE, BLACK));
      text__update(_clue->text[i], "0:0");
    }

  return _clue;
}

void clue__new_game(s_clue* fClue)
{
  for(int i=0; i<TRY; i++)
    {
      fClue->color[i] = 0;
      fClue->position[i] = 0;
      text__update(fClue->text[i], "0:0");
    }
}

void clue__update(s_clue* fClue, int fColor, int fPosition, int fTry)
{
  fClue->color[fTry] = fColor;
  fClue->position[fTry] = fPosition;

  char _str[STRMAX] = "";
  sprintf(_str, "%d:%d", fClue->position[fTry], fClue->color[fTry]);
  text__update(fClue->text[fTry], _str); 
}

void clue__blit(s_surface* fScreen, s_clue* fClue)
{
  for(int i=0; i<TRY; i++)
    {
      text__blit(fScreen, fClue->text[i], (s_pos){CLUE_X(i), CLUE_Y});
    }
}

void clue__free(s_clue* fClue)
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
