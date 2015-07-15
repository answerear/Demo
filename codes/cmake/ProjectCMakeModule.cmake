####################################################################################################
# Copyright Tiny Studio, 2015
# Created by aa
#
# This file suply some cmake module function help to setup project
####################################################################################################


# Set project name
# project_name : name of project
# Usage : SET_PROJECT_NAME(ProjectName)
FUNCTION(SET_PROJECT_NAME project_name)
	SET(LIB_NAME ${project_name} CACHE STRING "Library name")
	SET(BIN_NAME ${project_name} CACHE STRING "Binary name")
	STRING(TOUPPER ${LIB_NAME} LIB_NAME_TOUPPER)
ENDFUNCTION(SET_PROJECT_NAME)


# Add file to project
# type : "FILE"
# group : filter in Visual Studio project
# dir : file directory
# Usage : ADD_PROJECT_FILE("FILE" source ./source main.cpp)
FUNCTION(ADD_PROJECT_FILE type group dir)
	FOREACH(var ${ARGN})
		LIST(APPEND ${LIB_NAME}_${type} ${dir}${var})
		SOURCE_GROUP(${group} FILES ${dir}${var})
	ENDFOREACH(var)
ENDFUNCTION(ADD_PROJECT_FILE)


# Add file to project
# type : "FILE"
# group : filter in Visual Studio project
# dir : file directory
# ext : file extension
# Usage : ADD_PROJECT_FILE_BY_EXT("FILE" source ./source .cpp)
FUNCTION(ADD_PROJECT_FILE_BY_EXT type group dir ext)
	FILE(GLOB var ${dir}*${ext})
	
	FOREACH(f ${var})
		GET_FILENAME_COMPONENT(name ${f} NAME_WE)
		ADD_PROJECT_FILE(${type} ${group} ${dir} "${name}${ext}")
	ENDFOREACH(f)
ENDFUNCTION(ADD_PROJECT_FILE_BY_EXT)


FUNCTION(ADD_PROJECT_FILES group dir)
	FOREACH(var ${ARGN})
		LIST(APPEND ${LIB_NAME}_FILE ${dir}${var})
		SOURCE_GROUP(${group} FILES ${dir}${var})
	ENDFOREACH(var)
ENDFUNCTION(ADD_PROJECT_FILES)


FUNCTION(ADD_PROJECT_FILES_BY_EXT group dir ext)
	FILE(GLOB var ${dir}*${ext})
	
	FOREACH(f ${var})
		GET_FILENAME_COMPONENT(name ${f} NAME_WE)
		ADD_PROJECT_FILES(${group} ${dir} "${name}${ext}")
	ENDFOREACH()
ENDFUNCTION(ADD_PROJECT_FILES_BY_EXT)
	