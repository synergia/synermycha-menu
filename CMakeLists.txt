cmake_minimum_required(VERSION 3.10)

# project name
project(menu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

find_package (Threads)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
add_executable(menu main.cpp Menu.cpp MenuPage.cpp MenuOption.cpp DisplayBuffor.cpp ConfigInlineP.cpp)

target_link_libraries(menu ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})