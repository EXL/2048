# Qt 1 Port Modern Source Code
# https://github.com/heliocastro/qt1

cmake_minimum_required(VERSION 3.5)

project(2048-Qt1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_CODE 2048-Qt1.cpp)
set(MOC_FILE 2048-Qt1.moc)

set(QT1_DIR "/home/exl/Projects/qt1")
set(MOC_BIN "${QT1_DIR}/src/moc/moc-qt1")
include_directories("${QT1_DIR}/include")
link_directories("${QT1_DIR}/src")

add_custom_command(
	OUTPUT ${MOC_FILE}
	COMMAND ${MOC_BIN} ${CMAKE_SOURCE_DIR}/${SOURCE_CODE} -o ${CMAKE_SOURCE_DIR}/${MOC_FILE}
)

add_executable(${PROJECT_NAME} ${SOURCE_CODE} ${MOC_FILE})
target_link_libraries(${PROJECT_NAME} qt1)
