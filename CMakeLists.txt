cmake_minimum_required(VERSION 3.10)

# project name
project(menu)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(.)

find_package (Threads)

list(APPEND SOURCE_PATHS
    .
    menu/
    menu/config_inline/
    utils/
    )

foreach(SOURCE ${SOURCE_PATHS})
    aux_source_directory(${SOURCE} SOURCES)
endforeach()
    
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
add_executable(menu ${SOURCES})

target_link_libraries(menu ${CURSES_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})