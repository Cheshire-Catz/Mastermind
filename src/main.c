#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../include/mastermind.h"

int main(int argc, char **argv)
{
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr, "SDL initialization error : %s !\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  
  if(TTF_Init() == -1)
    {
      fprintf(stderr, "SDL_TTF initialization error : %s ! \n", TTF_GetError());
      exit(EXIT_FAILURE);
    }

  s_mastermind* _mastermind = mastermind__init(0);
  mastermind__play(_mastermind);
  mastermind__free(_mastermind);
  
  return EXIT_SUCCESS;
}
