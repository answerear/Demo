####################################################################################################
# Copyright Tiny Studio, 2015
# Created by aa
# 
# This cmake file to generate log project
####################################################################################################

# Set project name
SET_PROJECT_NAME(log)

IF (MSVC)
	IF (BUILD_SHARED_LIBS)
		ADD_DEFINITIONS(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
	ENDIF (BUILD_SHARED_LIBS)
ENDIF (MSVC)


SET(SOURCE_DIR ".")
SET(PLATFORM_DIR "${SOURCE_DIR}/../../common/platform")


# Setup include directories
INCLUDE_DIRECTORIES(
	"${SOURCE_DIR}/include"
	"${SOURCE_DIR}/include/service"
	"${PLATFORM_DIR}/include"
	"${PLATFORM_DIR}/include/console"
	"${PLATFORM_DIR}/include/io"
	"${PLATFORM_DIR}/include/thread"
	"${PLATFORM_DIR}/include/time"
	)

IF (WINDOWS)
	INCLUDE_DIRECTORIES(
		"${DEPENDENCIES_DIR}/pthread/include"
		)
ENDIF (WINDOWS)

# Setup link directories

IF (WINDOWS)
	IF (CMAKE_CL_64)
		LINK_DIRECTORIES(${DEPENDENCIES_DIR}/pthread/lib/x64)
	ELSE (CMAKE_CL_64)
		LINK_DIRECTORIES(${DEPENDENCIES_DIR}/pthread/lib/x86)
	ENDIF (CMAKE_CL_64)
ENDIF (WINDOWS)


# Setup project source files
SET_PROJECT_FILES(include ${SOURCE_DIR}/include/ .h)
SET_PROJECT_FILES(include\\\\service ${SOURCE_DIR}/include/service/ .h)

SET_PROJECT_FILES(source ${SOURCE_DIR}/source/ .cpp)
SET_PROJECT_FILES(source\\\\service ${SOURCE_DIR}/source/service/ .cpp)


IF (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} SHARED ${SOURCE_FILES})
ELSE (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} STATIC ${SOURCE_FILES})
ENDIF (BUILD_SHARED_LIBS)


IF (WINDOWS)
	TARGET_LINK_LIBRARIES(
		${LIB_NAME}
		platform
		pthreadVC2
		)
	
	ADD_CUSTOM_COMMAND(TARGET ${LIB_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${BIN_NAME}.dll" "${BIN_DIR}")
ELSEIF (MACOSX)
ELSEIF (LINUX)
ELSEIF (IOS)
ELSEIF (ANDROID)
ENDIF (WINDOWS)
