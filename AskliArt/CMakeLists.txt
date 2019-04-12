cmake_minimum_required (VERSION 2.6)
project (AskliArt)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(askliart askli_art.c)
target_link_libraries(askliart ${CURSES_LIBRARIES})
