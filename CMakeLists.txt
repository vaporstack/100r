cmake_minimum_required(VERSION 3.0)


set(project_name 100r)

project(${project_name})

set (${project_name}_VERSION_MAJOR 0)
set (${project_name}_VERSION_MINOR 0)
set (${project_name}_VERSION_PATCH 1)

option(BuildLibrary "Build ${project_name} static library" ON)
option(BuildDocumentation "BuildDocumentation" OFF)
option(BuildDemo "BuildDemo" OFF)
option(BuildTest "BuildTest" OFF)

macro(use_c99)
  if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
    endif()
  else()
    set(CMAKE_C_STANDARD 99)
  endif()
endmacro(use_c99)

use_c99()

if(BuildTest)
	add_subdirectory(test)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

if(CMAKE_BUILD_TYPE)
	if (${CMAKE_BUILD_TYPE} STREQUAL "release")
		set(BuildDocumentation ON)
	else()
		set(CMAKE_BUILD_TYPE "debug")
	endif()
else()
	set(CMAKE_BUILD_TYPE "debug")
endif()

message("CMAKE build type:" ${CMAKE_BUILD_TYPE})

message(${project_name})

if (CMAKE_BUILD_TYPE EQUAL "debug")

else()

endif ()


find_package(LibXml2)

if(${LIBXML2_FOUND})
	message('woooo')
	message(asdf, fu, ${LIBXML2_INCLUDE_DIR})
	include_directories(${LIBXML2_INCLUDE_DIR})
	set(LIBS ${LIBS} ${LIBXML2_LIBRARIES})
	add_definitions(-DHAVE_BACKEND_XML2)
endif()

##
#find_library( libxml2 LIBXML2)
#if ( ${LIBXML2} )
#	message('yay')
#	include_directories(${LIBXML2_INCLUDE_DIRS})
#	#include_directories(${LibGLFW_INCLUDE_DIRS})
#endif()

#if (${have_r4_environment})
#	message("Enabling the JSON backend?")
#	add_definitions(-DWSH_ENABLE_SERIAL_BACKEND_JSON)
#endif()

if(BuildLibrary)
	message("Adding library target.")
	file(GLOB sources src/*.c src/private/*.c contrib/cjson/cJSON.c)
	add_library(${project_name} STATIC ${sources} ${LIBS})
endif()


if(BuildDemo)
	find_package(LibGLFW )
	include_directories(${LibGLFW_INCLUDE_DIRS})
	set(LIBS ${LIBS} ${LibGLFW_LIBRARIES})

	if (GLFW_FOUND)
		if (${CMAKE_BUILD_TYPE} STREQUAL "release")
			set(BuildDemo YES)
		endif()

	else()
		message("Did not find GLFW, cannot build demo.")
		set(BuildDemo NO)

	endif()
endif()


#find_package(LibFTGL )
#include_directories(${LibGLFW_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${LibGLFW_LIBRARIES})
#if (FTGL_FOUND)
#	add_definitions(-DWSH_DEMO_ENABLE_FTGL)
#else()
#	message("Did not find FTGL.")
#endif()


if (${BuildDemo})
	message("Adding demo to build targets.")
	add_subdirectory(demo)
endif()

if (${BuildDoc})
	message("Adding documentation to build targets.")

	set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
	set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	configure_file(${doxyfile_in} ${doxyfile} @ONLY)

	message("Doxygen build started.")
	add_custom_target(
		doc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
		      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		      COMMENT "Generating API documentation with Doxygen"
		      VERBATIM)
endif()


target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/contrib)


#target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
#target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
#target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)

