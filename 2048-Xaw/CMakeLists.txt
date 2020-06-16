cmake_minimum_required(VERSION 3.5)

project(2048-Xaw LANGUAGES C)

add_subdirectory(../src/ ${PROJECT_BINARY_DIR}/src/)

set(SOURCE_CODE 2048-Xaw.c)

include_directories(../src/)

add_executable(${PROJECT_NAME} ${SOURCE_CODE})
target_link_libraries(${PROJECT_NAME} Xaw Xt X11 2048)
