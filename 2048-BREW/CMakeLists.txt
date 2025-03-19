########################################################################################################################
# CMake build script for Qualcomm BREW: 25-Jun-2024
#
cmake_minimum_required(VERSION 3.16)

########################################################################################################################
# Project section: 2048-BREW
#
project(2048-BREW LANGUAGES C VERSION "1.0.0")

include_directories(
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/../src
)

add_brew_module(brew_2048
	${BREW_PLATFORM_SDK_ROOT}/src/AEEModGen.c
	${BREW_PLATFORM_SDK_ROOT}/src/AEEAppGen.c

	${PROJECT_SOURCE_DIR}/../src/2048.c
	brew_2048.c
)
