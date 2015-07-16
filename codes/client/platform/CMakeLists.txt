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


# Setup project source files
ADD_PROJECT_FILES_BY_EXT(include ${SOURCE_DIR}/include/ .h)
ADD_PROJECT_FILES_BY_EXT(include\\\\\\\\adapter ${SOURCE_DIR}/include/adapter/ .h)
ADD_PROJECT_FILES_BY_EXT(include\\\\\\\\adapter\\\\\\\\android ${SOURCE_IDR}/include// .h)

ADD_PROJECT_FILES_BY_EXT(source ${SOURCE_DIR}/source/ .cpp)
ADD_PROJECT_FILES_BY_EXT(source ${SOURCE_DIR}/source/core/ .cpp)
ADD_PROJECT_FILES_BY_EXT(source ${SOURCE_DIR}/source/base_param/ .cpp)

IF (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} SHARED ${${LIB_NAME}_FILE})
ELSE (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} STATIC ${${LIB_NAME}_FILE})
ENDIF (BUILD_SHARED_LIBS)

TARGET_LINK_LIBRARIES(${LIB_NAME})
