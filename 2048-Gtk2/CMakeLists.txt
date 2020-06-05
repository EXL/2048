cmake_minimum_required(VERSION 3.5)

project(2048-Gtk2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_CODE 2048-Gtk2.cpp)

find_package(GTK2 REQUIRED gtk)

include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
#add_definitions(${GTK2_CFLAGS_OTHER})

add_executable(${PROJECT_NAME} 2048-Gtk2.cpp)

target_link_libraries(${PROJECT_NAME} ${GTK2_LIBRARIES})
