cmake_minimum_required(VERSION 3.16)

project(2048-BREW LANGUAGES C VERSION "1.0.0")

include_directories(
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/../src
)

add_brew_module(2048-BREW
	${BREW_PLATFORM_SDK_ROOT}/src/AEEModGen.c
	${BREW_PLATFORM_SDK_ROOT}/src/AEEAppGen.c

	${PROJECT_SOURCE_DIR}/../src/2048.c
	2048-BREW.c
)
