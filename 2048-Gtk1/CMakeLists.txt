cmake_minimum_required(VERSION 3.5)

project(2048-Gtk1 LANGUAGES C)

add_subdirectory(../src/ ${PROJECT_BINARY_DIR}/src/)

set(SOURCE_CODE 2048-Gtk1.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK1 REQUIRED gtk+)

include_directories(../src/ ${GTK1_INCLUDE_DIRS})
link_directories(${GTK1_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_CODE})
target_link_libraries(${PROJECT_NAME} ${GTK1_LIBRARIES} 2048)
