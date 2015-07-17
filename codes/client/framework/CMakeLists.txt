####################################################################################################
# Copyright Tiny Studio, 2015
# Created by aa
# 
# This cmake file to generate framework project
####################################################################################################

# Set project name
SET_PROJECT_NAME(framework)

IF (MSVC)
	IF (BUILD_SHARED_LIBS)
		ADD_DEFINITIONS(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
	ENDIF (BUILD_SHARED_LIBS)
ENDIF (MSVC)


SET(SOURCE_DIR "../../common/framework")
SET(PLATFORM_DIR "${SOURCE_DIR}/../platform")

# Setup include directories
INCLUDE_DIRECTORIES(
	"${SOURCE_DIR}/include"
	"${SOURCE_DIR}/include/core"
	"${SOURCE_DIR}/include/base_param"
	"${PLATFORM_DIR}/include"
	"${PLATFORM_DIR}/include/thread"
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
SET_PROJECT_FILES(include\\\\core ${SOURCE_DIR}/include/core/ .h)
SET_PROJECT_FILES(include\\\\base_param ${SOURCE_DIR}/include/base_param/ .h)

SET_PROJECT_FILES(source ${SOURCE_DIR}/source/ .cpp)
SET_PROJECT_FILES(source\\\\core ${SOURCE_DIR}/source/core/ .cpp)
SET_PROJECT_FILES(source\\\\base_param ${SOURCE_DIR}/source/base_param/ .cpp)


IF (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} SHARED ${SOURCE_FILES})
ELSE (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} STATIC ${SOURCE_FILES})
ENDIF (BUILD_SHARED_LIBS)

IF (WINDOWS)
TARGET_LINK_LIBRARIES(
	${LIB_NAME}
	platform
	pthreadVC2)
ELSEIF (MACOSX)
ELSEIF (LINUX)
ELSEIF (IOS)
ELSEIF (ANDROID)
ENDIF (WINDOWS)
