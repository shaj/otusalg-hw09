cmake_minimum_required(VERSION 3.2)

set(PROJ_NAME l9)

project(${PROJ_NAME})

add_executable(${PROJ_NAME} main.cpp generators.cpp)

set_target_properties(${PROJ_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)



