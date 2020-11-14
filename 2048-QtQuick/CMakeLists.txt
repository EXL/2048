cmake_minimum_required(VERSION 3.5)

project(2048-QtQuick LANGUAGES CXX)

add_subdirectory(../src/ ${PROJECT_BINARY_DIR}/src/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_CODE 2048-QtQuick.cpp 2048-QtQuick.qrc)
include_directories(../src/)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

if(ANDROID)
	add_library(${PROJECT_NAME} SHARED ${SOURCE_CODE})
else()
	add_executable(${PROJECT_NAME} ${SOURCE_CODE})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick 2048)
