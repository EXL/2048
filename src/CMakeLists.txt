cmake_minimum_required(VERSION 3.5)

project(2048 LANGUAGES C)

set(SOURCE_FILES 2048.c)
set(HEADER_FILES 2048.h)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
