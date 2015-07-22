# CMake entry point
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# It ensures that when Find*.cmake files included from cmake's Modules dir
# include another *.cmake file with relative path, that file will be included
# also from cmake's Modules dir, to not clash with per-project files.
CMAKE_POLICY(SET CMP0017 NEW)

# Use new behaviour with cmake >= 3.1:
# Only interpret if() arguments as variables or keywords when unquoted.
IF (CMAKE_VERSION VERSION_GREATER 3.1)
    CMAKE_POLICY(SET CMP0054 NEW)
ENDIF ()


PROJECT(Demo)

OPTION(DEBUG_MODE "Debug or release?" ON)

IF (WIN32)
	OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)
ELSE (WIN32)
	OPTION(BUILD_SHARED_LIBS "Build shared libraries" OFF)
ENDIF (WIN32)

# Setup platform dependencies macro
IF (WIN32)
	ADD_DEFINITIONS(-DV_OS_WIN32)
#	SET(WINDOWS ON CACHE STRING "Windows")
ELSEIF (APPLE)
	ADD_DEFINITIONS(-DV_OS_MACOS)
#	SET(MACOSX ON CACHE STRING "Mac OSX")
ENDIF (WIN32)

# Setup debug or release mode
IF (DEBUG_MODE)
	SET(CMAKE_BUILD_TYPE DEBUG)
ELSE (DEBUG_MODE)
	SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF (DEBUG_MODE)

# Add cmake module path
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../cmake" "${PROJECT_SOURCE_DIR}/../cmake/Modules/")

INCLUDE(CocosBuildHelpers)
INCLUDE(CPack)
INCLUDE(ProjectCMakeModule)


MESSAGE("${CMAKE_CURRENT_SOURCE_DIR}")

SET(BIN_DIR "${PROJECT_BINARY_DIR}/bin" CACHE STRING "Output binary directory")
SET(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../resources" CACHE STRING "Resource directory")



ADD_CUSTOM_TARGET(setup_build)

ADD_CUSTOM_COMMAND(TARGET setup_build PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E 
	make_directory "${BIN_DIR}"
	COMMENT "Create directory ${BIN_DIR}/")

ADD_CUSTOM_COMMAND(TARGET setup_build PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E 
	copy_directory "${RESOURCE_DIR}" "${BIN_DIR}/resources/"
	COMMENT "Copy resource from ${RESOURCE_DIR} to ${BIN_DIR}/resources/")


# Setup dependencies directory
IF (WINDOWS)
	SET(DEPENDENCIES_DIR "${PROJECT_SOURCE_DIR}/../dependencies/win32")
ELSEIF ()
ENDIF (WINDOWS)


ADD_SUBDIRECTORY(platform)
ADD_SUBDIRECTORY(log)
ADD_SUBDIRECTORY(framework)
ADD_SUBDIRECTORY(game)

ADD_DEPENDENCIES(platform setup_build)
ADD_DEPENDENCIES(log platform setup_build)
ADD_DEPENDENCIES(framework log platform setup_build)
ADD_DEPENDENCIES(game cocos2d framework log platform setup_build)
