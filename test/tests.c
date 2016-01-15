#include <stdio.h>
#include <unistd.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../include/mastermind.h"

#define SUITE_1 11
#define SUITE_2 10

/*
  Tools to check some part of the structures
*/

int test__nb_good_positions(s_mastermind* fMastermind)
{
  int _nb = 0;
  
  for(int i=0; i<TARGET_SIZE; i++)
    _nb += (fMastermind->target[i] == fMastermind->window->board->answer[i][fMastermind->try]->color);

  return _nb;
}

int test__nb_try(s_mastermind* fMastermind)
{
  return fMastermind->try;
}

int test__answer_size(s_mastermind* fMastermind)
{
  return fMastermind->window->board->index;
}

int test__color_stack(s_mastermind* fMastermind)
{
  return fMastermind->window->choice->stack[fMastermind->window->choice->index];
}

s_mastermind* test__mastermind_init(int fSize, int fStack, int fTry, int fNbGoodPos)
{
  s_mastermind* _mastermind = mastermind__init(fTry);

  for(int i=0; i<TARGET_SIZE; i++)
    {
      if(i<fSize)
        mastermind__add_answer(_mastermind);

      if(fNbGoodPos > 0)
        _mastermind->target[i] = _mastermind->window->board->answer[i][fTry]->color;

      else
        _mastermind->target[i] = BLACK;

      fNbGoodPos--;
    }

  _mastermind->window->choice->stack[_mastermind->window->choice->index] = fStack;

  return _mastermind;
}

/*
  Tests implementations
*/

void test_1()
{
  s_mastermind* _mastermind = test__mastermind_init(4,2,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 2);
  CU_ASSERT_FALSE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 2);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 3);

  mastermind__free(_mastermind);
}

void test_2()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);

  mastermind__free(_mastermind);
}

void test_3()
{
  s_mastermind* _mastermind = test__mastermind_init(0,6,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 6);
  CU_ASSERT_FALSE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 6);
  CU_ASSERT_TRUE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 5);

  mastermind__free(_mastermind);
}

void test_4()
{
  s_mastermind* _mastermind = test__mastermind_init(0,1,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);
  CU_ASSERT_FALSE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);
  CU_ASSERT_TRUE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);

  mastermind__free(_mastermind);
}

void test_5()
{
  s_mastermind* _mastermind = test__mastermind_init(0,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);

  mastermind__free(_mastermind);
}

void test_6()
{
  s_mastermind* _mastermind = test__mastermind_init(1,5,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 5);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 6);

  mastermind__free(_mastermind);

  _mastermind = test__mastermind_init(1,5,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 5);
  CU_ASSERT_TRUE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 4);

  mastermind__free(_mastermind);
}

void test_7()
{
  s_mastermind* _mastermind = test__mastermind_init(3,3,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 3);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 4);

  mastermind__free(_mastermind);

  _mastermind = test__mastermind_init(3,3,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 3);
  CU_ASSERT_TRUE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 2);

  mastermind__free(_mastermind);
}

void test_8()
{
  s_mastermind* _mastermind = test__mastermind_init(2,1,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 2);

  mastermind__free(_mastermind);

  _mastermind = test__mastermind_init(2,1,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);
  CU_ASSERT_TRUE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);

  mastermind__free(_mastermind);
}

void test_9()
{
  s_mastermind* _mastermind = test__mastermind_init(1,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);

  mastermind__free(_mastermind);
}

void test_10()
{
  s_mastermind* _mastermind = test__mastermind_init(3,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);

  mastermind__free(_mastermind);
}

void test_11()
{
  s_mastermind* _mastermind = test__mastermind_init(2,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__add_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 0);
  CU_ASSERT_TRUE(mastermind__remove_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 1);
  CU_ASSERT_EQUAL(test__color_stack(_mastermind), 1);

  mastermind__free(_mastermind);
}

void test_12()
{
  s_mastermind* _mastermind = test__mastermind_init(3,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 3);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_13()
{
  s_mastermind* _mastermind = test__mastermind_init(2,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 2);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_14()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,0,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 1);
  CU_ASSERT_FALSE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_15()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,0,3);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 3);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 1);
  CU_ASSERT_FALSE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_16()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,8,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 8);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 9);
  CU_ASSERT_FALSE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_17()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,9,0);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 9);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 0);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 10);
  CU_ASSERT_TRUE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_18()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,9,3);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 9);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 3);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 10);
  CU_ASSERT_TRUE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_19()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,0,4);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 4);
  CU_ASSERT_TRUE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 1);
  CU_ASSERT_TRUE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_20()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,0,3);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 3);
  CU_ASSERT_FALSE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 1);
  CU_ASSERT_FALSE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

void test_21()
{
  s_mastermind* _mastermind = test__mastermind_init(4,0,9,4);

  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 4);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 9);
  CU_ASSERT_EQUAL(test__nb_good_positions(_mastermind), 4);
  CU_ASSERT_TRUE(mastermind__check_answer(_mastermind));
  CU_ASSERT_EQUAL(test__answer_size(_mastermind), 0);
  CU_ASSERT_EQUAL(test__nb_try(_mastermind), 10);
  CU_ASSERT_TRUE(mastermind__is_finished(_mastermind));
  
  mastermind__free(_mastermind);
}

/*
  Test manager
*/

int main(int argc, char** argv)
{

  if(CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  CU_pSuite pSuite = NULL;
  
  pSuite = CU_add_suite("Add or remove color functionality", NULL, NULL);
  if(pSuite == NULL)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  char _suite1Names[SUITE_1][STRMAX] = {"1\t Answer size:4\t Color stack:2",
                                        "2\t Answer size:4\t Color stack:0",
                                        "3\t Answer size:0\t Color stack:6",
                                        "4\t Answer size:0\t Color stack:1",
                                        "5\t Answer size:0\t Color stack:0",
                                        "6\t Answer size:1\t Color stack:5",
                                        "7\t Answer size:3\t Color stack:3",
                                        "8\t Answer size:2\t Color stack:1",
                                        "9\t Answer size:1\t Color stack:0",
                                        "10\t Answer size:3\t Color stack:0",
                                        "11\t Answer size:2\t Color stack:0"};
  
  CU_TestFunc _suite1Tests[SUITE_1] = {test_1, test_2, test_3, test_4, test_5, test_6, test_7, test_8, test_9, test_10, test_11};

  for(int i=0; i<SUITE_1; i++)
    {
      if(CU_add_test(pSuite, _suite1Names[i], _suite1Tests[i]) == NULL)
        {
          CU_cleanup_registry();
          return CU_get_error();
        }
    }

  pSuite = NULL;
  
  pSuite = CU_add_suite("Check functionality", NULL, NULL);
  if(pSuite == NULL)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  char _suite2Names[SUITE_2][STRMAX] = {"12\t Answer size:3\t Good positions:0\t Try:0",
                                        "13\t Answer size:2\t Good positions:0\t Try:0",
                                        "14\t Answer size:4\t Good positions:0\t Try:0",
                                        "15\t Answer size:4\t Good positions:3\t Try:0",
                                        "16\t Answer size:4\t Good positions:0\t Try:8",
                                        "17\t Answer size:4\t Good positions:0\t Try:9",
                                        "18\t Answer size:4\t Good positions:3\t Try:9",
                                        "19\t Answer size:4\t Good positions:4\t Try:0",
                                        "20\t Answer size:4\t Good positions:3\t Try:0",
                                        "21\t Answer size:4\t Good positions:4\t Try:9"};                                        

  CU_TestFunc _suite2Tests[SUITE_2] = {test_12, test_13, test_14, test_15, test_16, test_17, test_18, test_19, test_20, test_21};

  for(int i=0; i<SUITE_2; i++)
    {
      if(CU_add_test(pSuite, _suite2Names[i], _suite2Tests[i]) == NULL)
        {
          CU_cleanup_registry();
          return CU_get_error();
        }
    }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
