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

# Setup include directories
INCLUDE_DIRECTORIES(
	"${SOURCE_DIR}/include"
	"${SOURCE_DIR}/include/core"
	"${SOURCE_DIR}/include/base_param"
	)


# Setup project source files
ADD_PROJECT_FILES_BY_EXT(include ${SOURCE_DIR}/include/ .h)
ADD_PROJECT_FILES_BY_EXT(include\\\\\\\\core ${SOURCE_DIR}/include/core/ .h)
ADD_PROJECT_FILES_BY_EXT(include\\\\\\\\base_param ${SOURCE_IDR}/include/base_param/ .h)

ADD_PROJECT_FILES_BY_EXT(source ${SOURCE_DIR}/source/ .cpp)
ADD_PROJECT_FILES_BY_EXT(source\\\\\\\\core ${SOURCE_DIR}/source/core/ .cpp)
ADD_PROJECT_FILES_BY_EXT(source\\\\\\\\base_param ${SOURCE_DIR}/source/base_param/ .cpp)

SET(SOURCE_FILES ${${LIB_NAME}_FILES})

IF (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} SHARED ${SOURCE_FILES})
ELSE (BUILD_SHARED_LIBS)
	ADD_LIBRARY(${LIB_NAME} STATIC ${SOURCE_FILES})
ENDIF (BUILD_SHARED_LIBS)

TARGET_LINK_LIBRARIES(${LIB_NAME})
