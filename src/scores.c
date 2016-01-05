#include "scores.h"

struct scores* scores__init(SDL_Surface* fScreen)
{
  struct scores* _scores = malloc(sizeof(struct scores));

  _scores->player = 0;
  _scores->master = 0;
  
  _scores->text = text__init(SCORES_SIZE, surface__init(fScreen, WIDTH, SCORES_SIZE, BLACK));

  return _scores;
}

void scores__update(struct scores* fScores, bool fPlayerWon)
{
  if(fPlayerWon)
    {
      fScores->player++;
    }

  else
    {
      fScores->master++;
    }
}

void scores__blit(struct scores* fScores)
{
  char _str[STRMAX];
  sprintf(_str, "Player: %d Master: %d", fScores->player, fScores->master);
  
  text__blit(fScores->text, _str, CENTER, (SDL_Rect){0,BANNER_MARGIN});
}

void scores__free(struct scores* fScores)
{
  if(fScores != NULL)
    {
      if(fScores->text != NULL)
        text__free(fScores->text);
      
      free(fScores);
    }
}
