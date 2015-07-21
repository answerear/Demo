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


IF (WINDOWS)
	IF (BUILD_SHARED_LIBS)
		ADD_DEFINITIONS(-U_USRDLL -U_EXPORT_DLL_ -U_USEGUIDLL -U_USREXDLL -U_USRSTUDIODLL)
	ENDIF (BUILD_SHARED_LIBS)
ENDIF (WINDOWS)


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


SET(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../resources")


# Copy resources to binary directory
IF (MSVC)
	#get our resources
	ADD_CUSTOM_COMMAND(TARGET ${BIN_NAME} PRE_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy_directory
							${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources)
	#get our dlls
	ADD_CUSTOM_COMMAND(TARGET ${BIN_NAME} PRE_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy
						${CMAKE_CURRENT_SOURCE_DIR}/../external/win32-specific/gles/prebuilt/glew32.dll 
						${CMAKE_CURRENT_BINARY_DIR})

	ADD_CUSTOM_COMMAND(TARGET ${BIN_NAME} PRE_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy
						${CMAKE_CURRENT_SOURCE_DIR}/../external/win32-specific/zlib/prebuilt/zlib1.dll 
						${CMAKE_CURRENT_BINARY_DIR}/Debug)

	SET_TARGET_PROPERTIES(${BIN_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(${BIN_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
ELSE ()
ENDIF (MSVC)
