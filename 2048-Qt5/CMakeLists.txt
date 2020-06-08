cmake_minimum_required(VERSION 3.5)

project(2048-Qt5 LANGUAGES CXX)

add_subdirectory(../src/ ${PROJECT_BINARY_DIR}/src/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_CODE 2048-Qt5.cpp)
include_directories(../src/)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_CODE})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets 2048)
