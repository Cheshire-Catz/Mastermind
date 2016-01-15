#include "../include/window.h"

s_window* window__init()
{ 
  s_window* _window = malloc(sizeof(s_window));

  _window->screen = screen__init(BLACK);
    
  _window->scores = scores__init();  
  _window->board  = board__init();
  _window->choice = choice__init();
  
  return _window;
}

void window__new_game(s_window* fWindow, bool fPlayerWon)
{
  scores__update(fWindow->scores, fPlayerWon);
  board__new_game(fWindow->board);
  choice__new_game(fWindow->choice);
}

void window__display(s_window* fWindow)
{
  surface__update(fWindow->screen);
 
  scores__blit(fWindow->screen, fWindow->scores);
  board__blit(fWindow->screen, fWindow->board);
  choice__blit(fWindow->screen, fWindow->choice);
  
  screen__flip(fWindow->screen);
}

bool window__cursor_move(s_window* fWindow, int fDir)
{
  return choice__cursor_move(fWindow->choice, fDir);
}

bool window__add_answer(s_window* fWindow, int fTry)
{
  if(!board__is_full(fWindow->board) && choice__is_available(fWindow->choice))
    {
      board__add_answer(fWindow->board, choice__pick_color(fWindow->choice), fTry);
      return true;
    }

  return false;
}

bool window__remove_answer(s_window* fWindow, int fTry)
{
  if(!board__is_empty(fWindow->board))
    {
      choice__depick_color(fWindow->choice, board__remove_answer(fWindow->board, fTry));
      return true;
    }

  return false;
}

bool window__check_answer(s_window* fWindow, e_color* fTarget, int *fTry)
{
  int _nbcolors = 0, _nbpositions = 0;
  
  if(board__is_full(fWindow->board))
    {
      _nbcolors    = board__check_color(fWindow->board, fTarget, *fTry);
      _nbpositions = board__check_position(fWindow->board, fTarget, *fTry);

      board__update(fWindow->board, _nbcolors, _nbpositions, *fTry);
      (*fTry)++;
    }

  return (_nbcolors == 4) && (_nbpositions == 4);
}

void window__free(s_window* fWindow)
{
  if(fWindow != NULL)
    {
      if(fWindow->scores != NULL)
        scores__free(fWindow->scores);
      
      if(fWindow->board != NULL)
        board__free(fWindow->board);

      if(fWindow->choice != NULL)
        choice__free(fWindow->choice);
      
      if(fWindow->screen != NULL)
        surface__free(fWindow->screen);

      free(fWindow);
    }
}
