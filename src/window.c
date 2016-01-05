#include "window.h"

struct window* window__init(bool fDisplay)
{ 
  struct window* _window = malloc(sizeof(struct window));

  _window->screen = NULL;
  
  if(fDisplay)
    _window->screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  
  _window->scores = scores__init(_window->screen);  
  _window->board  = board__init(_window->screen);
  _window->choice = choice__init(_window->screen);
  
  return _window;
}

void window__new_game(struct window* fWindow, bool fPlayerWon)
{
  scores__update(fWindow->scores, fPlayerWon);
  board__new_game(fWindow->board);
  choice__new_game(fWindow->choice);
}

void window__display(struct window* fWindow)
{
  SDL_FillRect(fWindow->screen, NULL, SDL_MapRGB(fWindow->screen->format, 0, 0, 0));
 
  scores__blit(fWindow->scores);
  board__blit(fWindow->board);
  choice__blit(fWindow->choice);
  
  SDL_Flip(fWindow->screen);
}

bool window__cursor_move(struct window* fWindow, int fDir)
{
  return choice__cursor_move(fWindow->choice, fDir);
}

bool window__add_answer(struct window* fWindow, int fTry)
{
  if(!board__is_full(fWindow->board) && choice__is_available(fWindow->choice))
    {
      board__add_answer(fWindow->board, choice__pick_color(fWindow->choice), fTry);
      return true;
    }

  return false;
}

bool window__remove_answer(struct window* fWindow, int fTry)
{
  if(!board__is_empty(fWindow->board))
    {
      choice__depick_color(fWindow->choice, board__remove_answer(fWindow->board, fTry));
      return true;
    }

  return false;
}

bool window__check_answer(struct window* fWindow, enum color* fTarget, int *fTry)
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

int window__answer_size(struct window* fWindow)
{
  return board__answer_size(fWindow->board);
}

int window__targeted_color_stack(struct window* fWindow)
{
  return choice__targeted_color_stack(fWindow->choice);
}

void window__answer_random(struct window* fWindow, int fSize, int fTry)
{
  board__answer_random(fWindow->board, fSize, fTry);
}

void window__free(struct window* fWindow)
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
        SDL_FreeSurface(fWindow->screen);

      free(fWindow);
    }
}
