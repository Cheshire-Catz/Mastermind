#include "../include/choice.h"

s_choice* choice__init()
{
  s_choice* _choice = malloc(sizeof(s_choice));

  char _str[STRMAX] = "";
  sprintf(_str, "%d", INIT_STACK);
  
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

      _choice->text[i] = text__init(STACK_SIZE, surface__init(STACK_SIZE, STACK_SIZE, _choice->color[i]));

      text__update(_choice->text[i], _str);
      
      _choice->position[i] = (s_pos){CURSOR_X(i), CURSOR_Y};
    }
  
  _choice->index  = 0;
  _choice->cursor = surface__init(STACK_SIZE, STACK_SIZE, WHITE);
  
  return _choice;
}

void choice__new_game(s_choice* fChoice)
{
  char _str[STRMAX] = "";
  sprintf(_str, "%d", INIT_STACK);
  
  for(int i=0; i<NB_COLORS; i++)
    {
      fChoice->stack[i] = INIT_STACK;
      text__update(fChoice->text[i], _str);
    }
}

void choice__blit(s_surface* fScreen, s_choice* fChoice)
{
  surface__update(fChoice->cursor);
  surface__blit(fScreen, fChoice->cursor, (s_pos){CURSOR_X(fChoice->index), CURSOR_Y});
  
  for(int i=0; i<NB_COLORS; i++)
    {
      text__blit(fScreen, fChoice->text[i], (s_pos){STACK_X(i), STACK_Y});
    }
}

bool choice__cursor_move(s_choice* fChoice, int fDir)
{
  if(!((fChoice->index == 0 && fDir == -1) || (fChoice->index == NB_COLORS-1 && fDir == 1)))
    {
      fChoice->index += fDir;
      return true;
    }

  return false;
}

e_color choice__pick_color(s_choice* fChoice)
{
  char _str[STRMAX] = "";
  e_color _color = WHITE;
  
  if(fChoice->stack[fChoice->index] > 0)
    {
      _color = fChoice->color[fChoice->index];
      sprintf(_str, "%d", --fChoice->stack[fChoice->index]);
      text__update(fChoice->text[fChoice->index], _str);
    }

  return _color;
}

void choice__depick_color(s_choice* fChoice, e_color fColor)
{
  char _str[STRMAX] = "";
  
  for(int i=0; i<NB_COLORS; i++)
    {
      if(fChoice->color[i] == fColor)
        {
          sprintf(_str, "%d", ++fChoice->stack[i]);
          text__update(fChoice->text[i], _str);
          break;
        }
    }
}

bool choice__is_available(s_choice* fChoice)
{
  return fChoice->stack[fChoice->index] > 0;
}

void choice__free(s_choice* fChoice)
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
