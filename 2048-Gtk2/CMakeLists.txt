cmake_minimum_required(VERSION 3.5)

project(2048-Gtk2 LANGUAGES C)

add_subdirectory(../src/ ${PROJECT_BINARY_DIR}/src/)

set(SOURCE_CODE 2048-Gtk2.c)

find_package(GTK2 REQUIRED gtk)

include_directories(../src/ ${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_CODE})
target_link_libraries(${PROJECT_NAME} ${GTK2_LIBRARIES} 2048 m)
