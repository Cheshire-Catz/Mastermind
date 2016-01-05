#include <stdio.h>

#include "mastermind.h"

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

  struct mastermind* _mastermind = mastermind__init(true);
  mastermind__play(_mastermind);
  mastermind__free(_mastermind);
  
  return EXIT_SUCCESS;
}
