cmake_minimum_required(VERSION 2.6)

project(mastermind)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

FIND_PACKAGE(SDL REQUIRED)

FIND_PACKAGE(SDL_ttf REQUIRED)

INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

set(CMAKE_C_FLAGS "-std=c99 -g -O0 -Wall") 

link_libraries (
  ${SDL_LIBRARY}
  ${SDLTTF_LIBRARY}
)

file(

  GLOB_RECURSE
  
  source_files_main
  
  src/*

  interface/sdl/*
)

file(

  GLOB_RECURSE

  source_files_test

  src/*

  interface/no_sdl/*
  
  test/*
  
)

list (REMOVE_ITEM source_files_test "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

add_executable(

  mastermind

  ${source_files_main}
)

add_executable(

  unit_test

  ${source_files_test}
)

set_target_properties(

  unit_test

  PROPERTIES

  COMPILE_DEFINITIONS "TEST"

  LINK_FLAGS "-lcunit"
)
