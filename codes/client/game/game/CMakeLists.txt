####################################################################################################
# Copyright Tiny Studio, 2015
# Created by aa
# 
# This cmake file to generate game main project
####################################################################################################


# Set project name
SET_PROJECT_NAME(game)

# Set source directory
SET(SOURCE_DIR ".")
SET(PLATFORM_DIR "${SOURCE_DIR}/../../../common/platform")
SET(LOG_DIR "${SOURCE_DIR}/../../log")
SET(FRAMEWORK_DIR "${SOURCE_DIR}/../../../common/framework")


# Setup include directories
INCLUDE_DIRECTORIES(
	"${SOURCE_DIR}/app"
	"${SOURCE_DIR}/scene"
	)

IF (WINDOWS)
	INCLUDE_DIRECTORIES(
		"${SOURCE_DIR}/main/win32"
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
SET_PROJECT_FILES(app ${SOURCE_DIR}/app/ .h)
SET_PROJECT_FILES(app ${SOURCE_DIR}/app/ .cpp)

IF (WINDOWS)
	SET_PROJECT_FILES(main ${SOURCE_DIR}/main/win32/ .h)
	SET_PROJECT_FILES(main ${SOURCE_DIR}/main/win32/ .cpp)
ELSEIF (LINUX)
ELSEIF (MACOSX)
ELSEIF (IOS)
ELSEIF (ANDROID)
ENDIF (WINDOWS)

ADD_EXECUTABLE(
	${BIN_NAME} WIN32 
	${SOURCE_FILES}
	)

TARGET_LINK_LIBRARIES(
	${BIN_NAME}
	platform
	log
	framework
	cocos2d
	)

SET_TARGET_PROPERTIES(${BIN_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
SET_TARGET_PROPERTIES(${BIN_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
