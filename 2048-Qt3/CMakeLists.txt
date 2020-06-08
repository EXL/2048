cmake_minimum_required(VERSION 3.5)

project(2048-Qt3 LANGUAGES CXX)

add_subdirectory(../src/ ${PROJECT_BINARY_DIR}/src/)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_CODE 2048-Qt3.cpp)
set(MOC_FILE 2048-Qt3.moc)

set(QT3_DIR "/usr/lib64/qt-3.3")
set(MOC_BIN "${QT3_DIR}/bin/moc")
include_directories(../src/ "${QT3_DIR}/include")
link_directories("${QT3_DIR}/lib")

add_custom_command(
	OUTPUT ${MOC_FILE}
	COMMAND ${MOC_BIN} ${CMAKE_SOURCE_DIR}/${SOURCE_CODE} -o ${CMAKE_SOURCE_DIR}/${MOC_FILE}
)

add_executable(${PROJECT_NAME} ${SOURCE_CODE} ${MOC_FILE})
target_link_libraries(${PROJECT_NAME} qt-mt 2048)
