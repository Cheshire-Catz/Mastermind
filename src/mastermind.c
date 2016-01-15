#include "../include/mastermind.h"

s_mastermind* mastermind__init(int fTry)
{
  s_mastermind* _mastermind = malloc(sizeof(s_mastermind));

  srand(time(NULL));
  
  _mastermind->window = window__init();
  _mastermind->stop   = false;
  _mastermind->win    = false;
  _mastermind->try    = fTry;
  
  mastermind__build_target(_mastermind->target);
  
  return _mastermind;
}

void mastermind__new_game(s_mastermind* fMastermind)
{
  window__new_game(fMastermind->window, fMastermind->win);

  mastermind__build_target(fMastermind->target);
  
  fMastermind->win = false;
  fMastermind->try = 0;
}

void mastermind__build_target(e_color* fTarget)
{
  for(int i=0; i<TARGET_SIZE; i++)
    {
      fTarget[i] = rand()%NB_COLORS;
    }
}

bool mastermind__is_finished(s_mastermind* fMastermind)
{
  return fMastermind->stop || fMastermind->win || (fMastermind->try >= TRY);
}

bool mastermind__add_answer(s_mastermind* fMastermind)
{
  return window__add_answer(fMastermind->window, fMastermind->try);
}

bool mastermind__remove_answer(s_mastermind* fMastermind)
{
  return window__remove_answer(fMastermind->window, fMastermind->try);
}

bool mastermind__check_answer(s_mastermind* fMastermind)
{
  fMastermind->win = window__check_answer(fMastermind->window, fMastermind->target, &fMastermind->try);
  
  return fMastermind->win;
}

void mastermind__play(s_mastermind* fMastermind)
{
  while(!fMastermind->stop)
    { 
      while(!mastermind__is_finished(fMastermind))
        {    
          event__process(fMastermind);
          window__display(fMastermind->window);
        }

      mastermind__new_game(fMastermind);
    }
}

void mastermind__free(s_mastermind* fMastermind)
{
  if(fMastermind != NULL)
    {
      if(fMastermind->window != NULL)
        window__free(fMastermind->window);
      
      free(fMastermind);
    }
}
