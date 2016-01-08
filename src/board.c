#include "../include/board.h"

s_board* board__init()
{
  s_board* _board = malloc(sizeof(s_board));

  _board->index = 0;
  
  for(int i=0; i<TRY; i++)
    {
      for(int j=0; j<TARGET_SIZE; j++)
        {
          _board->answer[j][i] = surface__init(ANSWER_SIZE, ANSWER_SIZE, WHITE);
        }
    }
  
  _board->clue = clue__init();
  
  return _board;
}

void board__blit(s_surface* fScreen, s_board* fBoard)
{
  for(int i=0; i<TRY; i++)
    {
      for(int j=0; j<TARGET_SIZE; j++)
        {
          surface__update(fBoard->answer[j][i]);
          surface__blit(fScreen, fBoard->answer[j][i], (s_pos){ANSWER_X(i), ANSWER_Y(j)});
        }    
    }
  
  clue__blit(fScreen, fBoard->clue);
}

void board__new_game(s_board* fBoard)
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

void board__add_answer(s_board* fBoard, e_color fColor, int fTry)
{
  fBoard->answer[fBoard->index][fTry]->color = fColor;
  fBoard->index++;
}

e_color board__remove_answer(s_board* fBoard, int fTry)
{
  fBoard->index--;
  e_color _color = fBoard->answer[fBoard->index][fTry]->color;
  fBoard->answer[fBoard->index][fTry]->color = WHITE;
  
  return _color;
}

int board__check_position(s_board* fBoard, e_color* fTarget, int fTry)
{
  int _nbpositions = 0;
  
  for(int i=0; i<TARGET_SIZE; i++)
    {
      if(fBoard->answer[i][fTry]->color == fTarget[i])
        _nbpositions++;
    }

  return _nbpositions;
}

int board__check_color(s_board* fBoard, e_color* fTarget, int fTry)
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

void board__update(s_board* fBoard, int fNbColors, int fNbPositions, int fTry)
{
  clue__update(fBoard->clue, fNbColors, fNbPositions, fTry);
  
  fBoard->index = 0;
}

bool board__is_full(s_board* fBoard)
{
  return fBoard->index >= TARGET_SIZE;
}

bool board__is_empty(s_board* fBoard)
{
  return fBoard->index == 0;
}

int board__answer_size(s_board* fBoard)
{
  return fBoard->index;
}

void board__answer_random(s_board* fBoard, int fSize, int fTry)
{
  while(fBoard->index < fSize && fBoard->index < TARGET_SIZE)
    {
      fBoard->answer[fBoard->index][fTry]->color = rand()%NB_COLORS;
      fBoard->index++;
    }
}

void board__free(s_board* fBoard)
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
