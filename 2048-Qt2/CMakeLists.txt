## Please build port Qt 2 to modern system before compiling this project and then set the ${QT2_DIR} directory.
## https://github.com/heliocastro/qt2

cmake_minimum_required(VERSION 3.5)

project(2048-Qt2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_CODE 2048-Qt2.cpp)
set(MOC_FILE 2048-Qt2.moc)

set(QT2_DIR "/home/exl/Projects/qt2")
set(MOC_BIN "${QT2_DIR}/src/moc/moc-qt2")
include_directories("${QT2_DIR}/include")
link_directories("${QT2_DIR}/src")

add_custom_command(
	OUTPUT ${MOC_FILE}
	COMMAND ${MOC_BIN} ${CMAKE_SOURCE_DIR}/${SOURCE_CODE} -o ${CMAKE_SOURCE_DIR}/${MOC_FILE}
)

add_executable(${PROJECT_NAME} ${SOURCE_CODE} ${MOC_FILE})
target_link_libraries(${PROJECT_NAME} qt2)
