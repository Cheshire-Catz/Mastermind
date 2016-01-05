#include "choice.h"

struct choice* choice__init(SDL_Surface* fScreen)
{
  struct choice* _choice = malloc(sizeof(struct choice));

  _choice->color[0] = RED;
  _choice->color[1] = BROWN;
  _choice->color[2] = YELLOW;
  _choice->color[3] = GREEN;
  _choice->color[4] = BLUE;
  _choice->color[5] = PURPLE;
  _choice->color[6] = CYAN;
  _choice->color[7] = PINK;
  _choice->color[8] = ORANGE;

  for(int i=0; i<NB_COLORS; i++)
    {
      _choice->stack[i] = INIT_STACK;

      _choice->text[i] = text__init(STACK_SIZE, surface__init(fScreen, STACK_SIZE, STACK_SIZE, _choice->color[i]));
      
      _choice->position[i].x = CURSOR_X(i);
      _choice->position[i].y = CURSOR_Y;
    }
  
  _choice->index  = 0;
  _choice->cursor = surface__init(fScreen, STACK_SIZE, STACK_SIZE, WHITE);
  
  return _choice;
}

void choice__new_game(struct choice* fChoice)
{
  for(int i=0; i<NB_COLORS; i++)
    {
      fChoice->stack[i] = INIT_STACK;
    }
}

void choice__blit(struct choice* fChoice)
{
  char _str[STRMAX];
  
  for(int i=0; i<NB_COLORS; i++)
    {
      surface__update(fChoice->cursor);
      surface__blit(fChoice->cursor, (SDL_Rect){CURSOR_X(fChoice->index), CURSOR_Y});

      sprintf(_str, "%d", fChoice->stack[i]);
      text__blit(fChoice->text[i], _str, CENTER, (SDL_Rect){STACK_X(i), STACK_Y});
    }
}

bool choice__cursor_move(struct choice* fChoice, int fDir)
{
  if(!((fChoice->index == 0 && fDir == -1) || (fChoice->index == NB_COLORS-1 && fDir == 1)))
    {
      fChoice->index += fDir;
      return true;
    }

  return false;
}

enum color choice__pick_color(struct choice* fChoice)
{
  enum color _color = WHITE;
  
  if(fChoice->stack[fChoice->index] > 0)
    {
      fChoice->stack[fChoice->index]--;
      _color = fChoice->color[fChoice->index];
    }

  return _color;
}

void choice__depick_color(struct choice* fChoice, enum color fColor)
{
  for(int i=0; i<NB_COLORS; i++)
    {
      if(fChoice->color[i] == fColor)
        {
          fChoice->stack[i]++;
        }
    }
}

bool choice__is_available(struct choice* fChoice)
{
  return fChoice->stack[fChoice->index] > 0;
}

int choice__targeted_color_stack(struct choice* fChoice)
{
  return fChoice->stack[fChoice->index];
}

void choice__free(struct choice* fChoice)
{
  if(fChoice != NULL)
    {
      for(int i=0; i<NB_COLORS; i++)
        {
          if(fChoice->text[i] != NULL)
            text__free(fChoice->text[i]);
        }

      surface__free(fChoice->cursor);
      
      free(fChoice);
    }
}
