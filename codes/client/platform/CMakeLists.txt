####################################################################################################
# Copyright Tiny Studio, 2015
# Created by aa
# 
# This cmake file to generate platform project
####################################################################################################

# Set project name
SET_PROJECT_NAME(platform)


IF (MSVC)
	IF (BUILD_SHARED_LIBS)
		ADD_DEFINITIONS(-D${LIB_NAME_TOUPPER}_EXPORT -D_USRDLL)
	ENDIF (BUILD_SHARED_LIBS)
ENDIF (MSVC)


# set source directory
SET(SOURCE_DIR "../../common/platform")


# Setup include directories
INCLUDE_DIRECTORIES(
	"${SOURCE_DIR}/include"
	"${SOURCE_DIR}/include/adapter"
	"${SOURCE_DIR}/include/apn"
	"${SOURCE_DIR}/include/codec"
	"${SOURCE_DIR}/include/console"
	"${SOURCE_DIR}/include/device"
	"${SOURCE_DIR}/include/io"
	"${SOURCE_DIR}/include/memory"
	"${SOURCE_DIR}/include/network"
	"${SOURCE_DIR}/include/thread"
	"${SOURCE_DIR}/include/time"
	)


IF (WINDOWS)
	INCLUDE_DIRECTORIES(
		"${SOURCE_DIR}/include/adapter/win32"
		"${DEPENDENCIES_DIR}/pthread/include"
	)
ELSEIF (MACOSX)
	INCLUDE_DIRECTORIES(
		"${SOURCE_DIR}/include/adapter/osx"
		)
ELSEIF (LINUX)
	INCLUDE_DIRECTORIES(
		"${SOURCE_DIR}/include/adapter/linux"
		)
ELSEIF (IOS)
	INCLUDE_DIRECTORIES(
		"${SOURCE_DIR}/include/adapter/ios"
		)
ELSEIF (ANDROID)
	INCLUDE_DIRECTORIES(
		"${SOURCE_DIR}/include/adapter/android"
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


# Setup project header files
SET_PROJECT_FILES(include ${SOURCE_DIR}/include/ .h)
SET_PROJECT_FILES(include\\\\adapter ${SOURCE_DIR}/include/adapter/ .h)
SET_PROJECT_FILES(include\\\\apn ${SOURCE_DIR}/include/apn/ .h)
SET_PROJECT_FILES(include\\\\codec ${SOURCE_DIR}/include/codec/ .h)
SET_PROJECT_FILES(include\\\\console ${SOURCE_DIR}/include/console/ .h)
SET_PROJECT_FILES(include\\\\device ${SOURCE_DIR}/include/device/ .h)
SET_PROJECT_FILES(include\\\\io ${SOURCE_DIR}/include/io/ .h)
SET_PROJECT_FILES(include\\\\memory ${SOURCE_DIR}/include/memory/ .h)
SET_PROJECT_FILES(include\\\\network ${SOURCE_DIR}/include/network/ .h)
SET_PROJECT_FILES(include\\\\thread ${SOURCE_DIR}/include/thread/ .h)
SET_PROJECT_FILES(include\\\\time ${SOURCE_DIR}/include/time/ .h)

IF (WINDOWS)
	SET_PROJECT_FILES(include\\\\adapter\\\\win32 ${SOURCE_DIR}/include/adapter/win32/ .h)
ELSEIF (MACOSX)
	SET_PROJECT_FILES(include\\\\adapter\\\\unix ${SOURCE_DIR}/include/adapter/unix/ .h)
	SET_PROJECT_FILES(include\\\\adapter\\\\osx ${SOURCE_DIR}/include/adapter/osx/ .h)
ELSEIF (IOS)
	SET_PROJECT_FILES(include\\\\adapter\\\\unix ${SOURCE_DIR}/include/adapter/unix/ .h)
	SET_PROJECT_FILES(include\\\\adapter\\\\ios ${SOURCE_DIR}/include/adapter/ios/ .h)
ELSEIF (ANDROID)
	SET_PROJECT_FILES(include\\\\adapter\\\\unix ${SOURCE_DIR}/include/adapter/unix/ .h)
	SET_PROJECT_FILES(include\\\\adapter\\\\android ${SOURCE_IDR}/include/android/ .h)
ELSEIF (LINUX)
ENDIF (WINDOWS)


# Setup project source files
SET_PROJECT_FILES(source ${SOURCE_DIR}/source/ .cpp)
SET_PROJECT_FILES(source\\\\adapter ${SOURCE_DIR}/source/adapter/ .cpp)
SET_PROJECT_FILES(source\\\\apn ${SOURCE_DIR}/source/apn/ .cpp)
SET_PROJECT_FILES(source\\\\codec ${SOURCE_DIR}/source/codec/ .cpp)
SET_PROJECT_FILES(source\\\\console ${SOURCE_DIR}/source/console/ .cpp)
SET_PROJECT_FILES(source\\\\device ${SOURCE_DIR}/source/device/ .cpp)
SET_PROJECT_FILES(source\\\\io ${SOURCE_DIR}/source/io/ .cpp)
SET_PROJECT_FILES(source\\\\memory ${SOURCE_DIR}/source/memory/ .cpp)
SET_PROJECT_FILES(source\\\\network ${SOURCE_DIR}/source/network/ .cpp)
SET_PROJECT_FILES(source\\\\thread ${SOURCE_DIR}/source/thread/ .cpp)
SET_PROJECT_FILES(source\\\\time ${SOURCE_DIR}/source/time/ .cpp)

IF (WINDOWS)
	SET_PROJECT_FILES(source\\\\adapter\\\\win32 ${SOURCE_DIR}/source/adapter/win32/ .cpp)
ELSEIF (MACOSX)
	SET_PROJECT_FILES(source\\\\adapter\\\\unix ${SOURCE_DIR}/source/adapter/unix/ .cpp)
	SET_PROJECT_FILES(source\\\\adapter\\\\osx ${SOURCE_DIR}/source/adapter/osx/ .cpp)
ELSEIF (IOS)
	SET_PROJECT_FILES(source\\\\adapter\\\\unix ${SOURCE_DIR}/source/adapter/unix/ .cpp)
	SET_PROJECT_FILES(source\\\\adapter\\\\ios ${SOURCE_DIR}/source/adapter/ios/ .cpp)
ELSEIF (ANDROID)
	SET_PROJECT_FILES(source\\\\adapter\\\\unix ${SOURCE_DIR}/source/adapter/unix/ .cpp)
	SET_PROJECT_FILES(source\\\\adapter\\\\android ${SOURCE_IDR}/source/android/ .cpp)
ELSEIF (LINUX)
ENDIF (WINDOWS)


IF (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} SHARED ${SOURCE_FILES})
ELSE (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} STATIC ${SOURCE_FILES})
ENDIF (BUILD_SHARED_LIBS)


IF (WINDOWS)
	TARGET_LINK_LIBRARIES(
		${LIB_NAME}
		pthreadVC2
		Ws2_32
		)
	
	ADD_CUSTOM_COMMAND(TARGET ${LIB_NAME} PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${BIN_NAME}.dll" "${BIN_DIR}")
ELSEIF (MACOSX)
ELSEIF (LINUX)
ELSEIF (IOS)
ELSEIF (ANDROID)
ENDIF (WINDOWS)
