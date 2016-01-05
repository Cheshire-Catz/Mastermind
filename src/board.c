#include "board.h"

struct board* board__init(SDL_Surface* fScreen)
{
  struct board* _board = malloc(sizeof(struct board));

  for(int i=0; i<TRY; i++)
    {
      for(int j=0; j<TARGET_SIZE; j++)
        {
          _board->answer[j][i] = surface__init(fScreen, ANSWER_SIZE, ANSWER_SIZE, WHITE);
        }
    }
  
  _board->clue = clue__init(fScreen);
  
  return _board;
}

void board__blit(struct board* fBoard)
{
  for(int i=0; i<TRY; i++)
    {
      for(int j=0; j<TARGET_SIZE; j++)
        {
          surface__update(fBoard->answer[j][i]);
          surface__blit(fBoard->answer[j][i], (SDL_Rect){ANSWER_X(i), ANSWER_Y(j)});
        }    
    }
  
  clue__blit(fBoard->clue);
}

void board__new_game(struct board* fBoard)
{
  fBoard->index = 0;
  
  for(int i=0; i<TRY; i++)
    {
      for(int j=0; j<TARGET_SIZE; j++)
        {
          fBoard->answer[j][i]->color = WHITE;
        }

      clue__new_game(fBoard->clue);
   }
}

void board__add_answer(struct board* fBoard, enum color fColor, int fTry)
{
  fBoard->answer[fBoard->index][fTry]->color = fColor;
  fBoard->index++;
}

enum color board__remove_answer(struct board* fBoard, int fTry)
{
  fBoard->index--;
  enum color _color = fBoard->answer[fBoard->index][fTry]->color;
  fBoard->answer[fBoard->index][fTry]->color = WHITE;
  
  return _color;
}

int board__check_position(struct board* fBoard, enum color* fTarget, int fTry)
{
  int _nbpositions = 0;
  
  for(int i=0; i<TARGET_SIZE; i++)
    {
      if(fBoard->answer[i][fTry]->color == fTarget[i])
        _nbpositions++;
    }

  return _nbpositions;
}

int board__check_color(struct board* fBoard, enum color* fTarget, int fTry)
{
  int _nbcolors = 0;
  int _notchecked[TARGET_SIZE];

  for(int i=0; i<TARGET_SIZE; i++)
    {
      _notchecked[i] = 1;
    }

  for(int i=0; i<TARGET_SIZE; i++)
    {
      for(int j=0; j<TARGET_SIZE; j++)
        {
          if(_notchecked[j] && (fBoard->answer[i][fTry]->color == fTarget[j]))
            {
              _notchecked[j] = 0;
              _nbcolors++;
              break;
            }
        }
    }

  return _nbcolors;
}

void board__update(struct board* fBoard, int fNbColors, int fNbPositions, int fTry)
{
  clue__update(fBoard->clue, fNbColors, fNbPositions, fTry);
  
  fBoard->index = 0;
}

bool board__is_full(struct board* fBoard)
{
  return fBoard->index >= TARGET_SIZE;
}

bool board__is_empty(struct board* fBoard)
{
  return fBoard->index == 0;
}

int board__answer_size(struct board* fBoard)
{
  return fBoard->index;
}

void board__answer_random(struct board* fBoard, int fSize, int fTry)
{
  while(fBoard->index < fSize && fBoard->index < TARGET_SIZE)
    {
      fBoard->answer[fBoard->index][fTry]->color = rand()%NB_COLORS;
      fBoard->index++;
    }
}

void board__free(struct board* fBoard)
{
  if(fBoard != NULL)
    {
      for(int i=0; i<TRY; i++)
        {
          for(int j=0; j<TARGET_SIZE; j++)
            {
              if(fBoard->answer[j][i] != NULL)
                surface__free(fBoard->answer[j][i]);
            }
        }
      
      if(fBoard->clue != NULL)
        clue__free(fBoard->clue);
      
      free(fBoard);
    }
}
