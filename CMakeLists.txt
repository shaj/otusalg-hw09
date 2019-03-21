cmake_minimum_required(VERSION 3.2)

set(PROJ_NAME l9)

project(${PROJ_NAME})

add_executable(${PROJ_NAME} main.cpp generators.cpp)

set_target_properties(${PROJ_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)


# Отсюда
# https://stackoverflow.com/a/48910054
add_custom_target( unZip ALL)
add_custom_command(TARGET unZip PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_CURRENT_SOURCE_DIR}/wiki.tar.bz2
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/wiki.tar.bz2
	COMMENT "Unpacking wiki.tar.bz2"
	VERBATIM
)
