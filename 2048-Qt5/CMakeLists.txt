cmake_minimum_required(VERSION 3.5)

project(2048-Qt5 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_CODE 2048-Qt5.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(2048-Qt5 ${SOURCE_CODE})

target_link_libraries(2048-Qt5 PRIVATE Qt5::Widgets)
