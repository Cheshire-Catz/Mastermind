#include "mastermind.h"

struct mastermind* mastermind__init(bool fDisplay)
{
  struct mastermind* _mastermind = malloc(sizeof(struct mastermind));

  srand(time(NULL));
  
  _mastermind->window = window__init(fDisplay);
  _mastermind->stop   = false;
  _mastermind->win    = false;
  _mastermind->try    = 0;
  
  mastermind__build_target(_mastermind->target);
  
  return _mastermind;
}

void mastermind__new_game(struct mastermind* fMastermind)
{
  window__new_game(fMastermind->window, fMastermind->win);

  mastermind__build_target(fMastermind->target);
  
  fMastermind->win = false;
  fMastermind->try = 0;
}

void mastermind__build_target(enum color* fTarget)
{
  for(int i=0; i<TARGET_SIZE; i++)
    {
      fTarget[i] = rand()%NB_COLORS;
    }
}

bool mastermind__is_finished(struct mastermind* fMastermind)
{
  return fMastermind->stop || fMastermind->win || (fMastermind->try >= TRY);
}

void mastermind__play(struct mastermind* fMastermind)
{
  while(!fMastermind->stop)
    { 
      while(!mastermind__is_finished(fMastermind))
        {
          window__display(fMastermind->window);
          
          while(SDL_PollEvent(&fMastermind->event))
            {
              switch(fMastermind->event.type)
                {
                case SDL_QUIT:
                  fMastermind->stop = true;
                  break;
                  
                case SDL_KEYDOWN:
                  switch(fMastermind->event.key.keysym.sym)
                    {
                    case SDLK_LEFT:
                      window__cursor_move(fMastermind->window, -1);
                      break;
                      
                    case SDLK_RIGHT:
                      window__cursor_move(fMastermind->window, +1);
                      break;
                      
                    case SDLK_RETURN:
                      window__add_answer(fMastermind->window, fMastermind->try);
                      break;
                      
                    case SDLK_BACKSPACE:
                      window__remove_answer(fMastermind->window, fMastermind->try);
                      break;
                  
                    case SDLK_SPACE:
                      fMastermind->win = window__check_answer(fMastermind->window, fMastermind->target, &fMastermind->try);
                      break;
                      
                    default:
                      break;
                    }
                  break;
                  
                default:
                  break;
                }
            }
        }

      mastermind__new_game(fMastermind);
    }
}

void mastermind__free(struct mastermind* fMastermind)
{
  if(fMastermind != NULL)
    {
      if(fMastermind->window != NULL)
        window__free(fMastermind->window);
      
      free(fMastermind);
    }

  SDL_Quit();
}
