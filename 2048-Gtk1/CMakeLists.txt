cmake_minimum_required(VERSION 3.5)

project(2048-Gtk1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_CODE 2048-Gtk1.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK1 REQUIRED gtk+)

include_directories(${GTK1_INCLUDE_DIRS})
link_directories(${GTK1_LIBRARY_DIRS})
add_definitions(${GTK1_CFLAGS_OTHER})

add_executable(${PROJECT_NAME} 2048-Gtk1.cpp)

target_link_libraries(${PROJECT_NAME} ${GTK1_LIBRARIES})
