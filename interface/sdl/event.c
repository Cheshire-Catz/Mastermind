#include <SDL/SDL.h>

#include "../../include/event.h"

void event__process(s_mastermind* fMastermind)
{
  SDL_Event _event;
  
  while(SDL_PollEvent(&_event))
    {
      switch(_event.type)
        {
        case SDL_QUIT:
          fMastermind->stop = true;
          break;
                  
        case SDL_KEYDOWN:
          switch(_event.key.keysym.sym)
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
