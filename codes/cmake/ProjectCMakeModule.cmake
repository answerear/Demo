####################################################################################################
# Copyright Tiny Studio, 2015
# Created by aa
#
# This file suply some cmake module function help to setup project
####################################################################################################


# Set project name
# project_name : name of project
# Usage : SET_PROJECT_NAME(ProjectName)
MACRO(SET_PROJECT_NAME project_name)
	SET(LIB_NAME ${project_name})
	SET(BIN_NAME ${project_name})
	STRING(TOUPPER ${LIB_NAME} LIB_NAME_TOUPPER)
ENDMACRO(SET_PROJECT_NAME)


# Add file to project
# type : "FILE"
# group : filter in Visual Studio project
# dir : file directory
# Usage : ADD_PROJECT_FILE("FILE" source ./source main.cpp)
MACRO(ADD_PROJECT_FILE type group dir)
	FOREACH(var ${ARGN})
		LIST(APPEND ${LIB_NAME}_${type} ${dir}${var})
		SOURCE_GROUP(${group} FILES ${dir}${var})
	ENDFOREACH(var)
ENDMACRO(ADD_PROJECT_FILE)


# Add file to project
# type : "FILE"
# group : filter in Visual Studio project
# dir : file directory
# ext : file extension
# Usage : ADD_PROJECT_FILE_BY_EXT("FILE" source ./source .cpp)
MACRO(ADD_PROJECT_FILE_BY_EXT type group dir ext)
	FILE(GLOB var ${dir}*${ext})
	
	FOREACH(f ${var})
		GET_FILENAME_COMPONENT(name ${f} NAME_WE)
		ADD_PROJECT_FILE(${type} ${group} ${dir} "${name}${ext}")
	ENDFOREACH(f)
ENDMACRO(ADD_PROJECT_FILE_BY_EXT)


MACRO(ADD_PROJECT_FILES group dir)
	FOREACH(var ${ARGN})
		LIST(APPEND ${LIB_NAME}_FILES ${dir}${var})
		SOURCE_GROUP(${group} FILES ${dir}${var})
	ENDFOREACH(var)
ENDMACRO(ADD_PROJECT_FILES)


MACRO(ADD_PROJECT_FILES_BY_EXT group dir ext)
	MESSAGE(${group})
	FILE(GLOB var ${dir}*${ext})
	
	FOREACH(f ${var})
		GET_FILENAME_COMPONENT(name ${f} NAME_WE)
		ADD_PROJECT_FILES(${group} ${dir} "${name}${ext}")
	ENDFOREACH()
ENDMACRO(ADD_PROJECT_FILES_BY_EXT)
	