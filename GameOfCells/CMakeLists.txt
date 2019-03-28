cmake_minimum_required (VERSION 2.6)
project (GameOfCells)

find_package (Curses REQUIRED)
include_directories (${CURSES_INCLUDE_DIR})

add_executable (gameofcells gameofcells.c)
target_link_libraries (gameofcells ${CURSES_LIBRARIES})
