#include <stdio.h>
#include <unistd.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../include/mastermind.h"

// Test 1 : answer size 4, targeted color stack 2
void test_1()
{
  struct mastermind* _mastermind = mastermind__init();

  for(int i=0; i<4; i++)
    window__add_answer(_mastermind->window, _mastermind->try);

  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 4);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 2);
  CU_ASSERT_FALSE(window__add_answer(_mastermind->window, _mastermind->try));
  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 4);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 2);
  CU_ASSERT_TRUE(window__remove_answer(_mastermind->window, _mastermind->try));
  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 3);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 3);

  mastermind__free(_mastermind);
}

// Test 2 : answer size 4, targeted color stack 0 
void test_2()
{
  struct mastermind* _mastermind = mastermind__init();

  for(int i=0; i<4; i++)
    window__add_answer(_mastermind->window, _mastermind->try);

  window__check_answer(_mastermind->window, _mastermind->target, &_mastermind->try);  
  window__cursor_move(_mastermind->window, 1);
  window__add_answer(_mastermind->window, _mastermind->try);
  window__add_answer(_mastermind->window, _mastermind->try);
  window__cursor_move(_mastermind->window, -1);
  window__add_answer(_mastermind->window, _mastermind->try);
  window__add_answer(_mastermind->window, _mastermind->try);

  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 4);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 0);
  CU_ASSERT_FALSE(window__add_answer(_mastermind->window, _mastermind->try));
  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 4);
  CU_ASSERT_TRUE(window__remove_answer(_mastermind->window, _mastermind->try));
  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 3);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 1);

  mastermind__free(_mastermind);
}

// Test 3 : answer size 0, targeted color stack 6
void test_3()
{
  struct mastermind* _mastermind = mastermind__init();

  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 0);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 6);
  CU_ASSERT_FALSE(window__remove_answer(_mastermind->window, _mastermind->try));
  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 0);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 6);
  CU_ASSERT_TRUE(window__add_answer(_mastermind->window, _mastermind->try));
  CU_ASSERT_EQUAL(window__answer_size(_mastermind->window), 1);
  CU_ASSERT_EQUAL(window__targeted_color_stack(_mastermind->window), 5);

  mastermind__free(_mastermind);
}

int main(int argc, char** argv)
{
  CU_pSuite pSuite = NULL;

  if(CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  pSuite = CU_add_suite("Variant 1", NULL, NULL);
  if(pSuite == NULL)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(CU_add_test(pSuite, "Test 1", test_1) == NULL)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if(CU_add_test(pSuite, "Test 2", test_2) == NULL)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  pSuite = CU_add_suite("Variant 2", NULL, NULL);

  if(CU_add_test(pSuite, "Test 3", test_3) == NULL)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
