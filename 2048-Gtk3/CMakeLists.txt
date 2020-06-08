cmake_minimum_required(VERSION 3.5)

project(2048-Gtk3 LANGUAGES C)

add_subdirectory(../src/ ${PROJECT_BINARY_DIR}/src/)

set(SOURCE_CODE 2048-Gtk3.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(../src/ ${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(${PROJECT_NAME} ${SOURCE_CODE})
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES} 2048 m)
