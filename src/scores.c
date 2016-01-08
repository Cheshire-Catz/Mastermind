#include "../include/scores.h"

s_scores* scores__init()
{
  s_scores* _scores = malloc(sizeof(s_scores));

  _scores->player = 0;
  _scores->master = 0;
  
  _scores->text = text__init(SCORES_SIZE, surface__init(WIDTH, SCORES_SIZE, BLACK));

  text__update(_scores->text, "Player: 0 Master: 0");

  return _scores;
}

void scores__update(s_scores* fScores, bool fPlayerWon)
{
  char _str[STRMAX] = "";
  
  if(fPlayerWon)
    {
      sprintf(_str, "Player: %d Master: %d", ++fScores->player, fScores->master);
    }

  else
    {
      sprintf(_str, "Player: %d Master: %d", fScores->player, ++fScores->master);
    }

  text__update(fScores->text, _str);
}

void scores__blit(s_surface* fScreen, s_scores* fScores)
{
  text__blit(fScreen, fScores->text, (s_pos){0,BANNER_MARGIN});
}

void scores__free(s_scores* fScores)
{
  if(fScores != NULL)
    {
      if(fScores->text != NULL)
        text__free(fScores->text);
      
      free(fScores);
    }
}
