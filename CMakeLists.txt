cmake_minimum_required(VERSION 3.2)

set(PROJ_NAME l8)

project(${PROJ_NAME})

add_executable(${PROJ_NAME}-sel main-sel.cpp generators.cpp)

set_target_properties(${PROJ_NAME}-sel PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)


# add_executable(${PROJ_NAME}-trie main-trie.cpp generators.cpp)

# set_target_properties(${PROJ_NAME}-trie PROPERTIES
#   CXX_STANDARD 14
#   CXX_STANDARD_REQUIRED ON
#   COMPILE_OPTIONS -Wpedantic -Wall -Wextra
# )


