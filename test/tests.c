#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "../include/mastermind.h"

// Test 1 : answer size 4, targeted color stack 2
void test_1()
{
  printf("Test 1 ... ");
  
  struct mastermind* _mastermind = mastermind__init();

  // Initialization
  for(int i=0; i<4; i++)
    window__add_answer(_mastermind->window, _mastermind->try);

  // Test
  assert(window__answer_size(_mastermind->window) == 4);
  assert(window__targeted_color_stack(_mastermind->window) == 2);
  assert(!window__add_answer(_mastermind->window, _mastermind->try));
  assert(window__answer_size(_mastermind->window) == 4);
  assert(window__remove_answer(_mastermind->window, _mastermind->try));
  assert(window__answer_size(_mastermind->window) == 3);
  assert(window__targeted_color_stack(_mastermind->window) == 3);

  mastermind__free(_mastermind);
  
  printf("OK!\n");
}

// Test 2 : answer size 4, targeted color stack 0 
void test_2()
{
  printf("Test 2 ... ");

  struct mastermind* _mastermind = mastermind__init();

  // Initialization
  for(int i=0; i<4; i++)
    window__add_answer(_mastermind->window, _mastermind->try);
  
  window__check_answer(_mastermind->window, _mastermind->target, &_mastermind->try);  
  window__cursor_move(_mastermind->window, 1);
  window__add_answer(_mastermind->window, _mastermind->try);
  window__add_answer(_mastermind->window, _mastermind->try);
  window__cursor_move(_mastermind->window, -1);
  window__add_answer(_mastermind->window, _mastermind->try);
  window__add_answer(_mastermind->window, _mastermind->try);

  // Test
  assert(window__answer_size(_mastermind->window) == 4);
  assert(window__targeted_color_stack(_mastermind->window) == 0);
  assert(!window__add_answer(_mastermind->window, _mastermind->try));
  assert(window__answer_size(_mastermind->window) == 4);
  assert(window__remove_answer(_mastermind->window, _mastermind->try));
  assert(window__answer_size(_mastermind->window) == 3);
  assert(window__targeted_color_stack(_mastermind->window) == 1);

  mastermind__free(_mastermind);
   
  printf("OK!\n");
}

// Test 3 : answer size 0, targeted color stack 6
void test_3()
{
  printf("Test 3 ... ");

  struct mastermind* _mastermind = mastermind__init();

  assert(window__answer_size(_mastermind->window) == 0);
  assert(window__targeted_color_stack(_mastermind->window) == 6);
  assert(!window__remove_answer(_mastermind->window, _mastermind->try));
  assert(window__answer_size(_mastermind->window) == 0);
  assert(window__targeted_color_stack(_mastermind->window) == 6);
  assert(window__add_answer(_mastermind->window, _mastermind->try));
  assert(window__answer_size(_mastermind->window) == 1);
  assert(window__targeted_color_stack(_mastermind->window) == 5);

  mastermind__free(_mastermind);
  
  printf("OK!\n");
}

int main(int argc, char** argv)
{
  printf("\nVariant 1\n");
  test_1();
  test_2();

  printf("\nVariant 2\n");
  test_3();
  
  return EXIT_SUCCESS;
}
