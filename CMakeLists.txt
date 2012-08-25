#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

PROJECT (ircAutomat)

SET (APPLICATION_NAME "${CMAKE_PROJECT_NAME}")
SET (APPLICATION_CODENAME "${CMAKE_PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2012")
SET (APPLICATION_VERSION_MAJOR 0)
SET (APPLICATION_VERSION_MINOR 1)
SET (APPLICATION_VERSION_PATCH 0)
SET (APPLICATION_VERSION_TYPE SNAPSHOT)

SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")

SET (APPLICATION_VENDOR_URL "mageta.org")
SET (APPLICATION_VENDOR_NAME "${APPLICATION_VENDOR_URL}")
SET (APPLICATION_VENDOR_ID "org.mageta")
SET (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${CMAKE_PROJECT_NAME}")

#
# Some Project-Options
#

OPTION( Testing		"Testing"		ON )

OPTION( Optimize	"Optimize"		ON )
OPTION( Profile		"Profile"		OFF )
OPTION( Debug		"Debug"			ON )
OPTION( DebugMake	"Verbose Make Output"	OFF )
OPTION( Plugins		"Build Plugins"		ON )

#
# Some more Options but rather static ones
#

SET ( C++11			ON )
SET ( C99			ON )
SET ( Require_GNU		ON )
SET ( Require_GCC_VERSION	4.6 )
SET ( Require_NIX		ON )

#
# Compiler-Checks
#

if(Require_GNU)
	if(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)
		message(STATUS "Compiler-Toolchain is GNU..")
	else(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)
		message(FATAL_ERROR "Compiler-Toolchain is NOT GNU..")
	endif(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)

	if(Require_GCC_VERSION)
		execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

		if(GCC_VERSION VERSION_GREATER ${Require_GCC_VERSION} OR GCC_VERSION VERSION_EQUAL ${Require_GCC_VERSION})
			message(STATUS "GCC-Version is >= ${Require_GCC_VERSION}..")
		else(GCC_VERSION VERSION_GREATER ${Require_GCC_VERSION} OR GCC_VERSION VERSION_EQUAL ${Require_GCC_VERSION})
			message(FATAL_ERROR "GCC-Version is < ${Require_GCC_VERSION}..")
		endif(GCC_VERSION VERSION_GREATER ${Require_GCC_VERSION} OR GCC_VERSION VERSION_EQUAL ${Require_GCC_VERSION})
	endif(Require_GCC_VERSION)
endif(Require_GNU)

#
# Misc Checks
#

if(Require_NIX)
	if(CMAKE_HOST_UNIX)
		message(STATUS "Host-System is *NIX..")
	else(CMAKE_HOST_UNIX)
		message(STATUS "Host-System is not *NIX..")
	endif(CMAKE_HOST_UNIX)
endif(Require_NIX)

#
# Compiler-Options
#

if(Debug)
	add_definitions(-DDEBUG)

	message(STATUS "Debug-Options: ON..")

	set( CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -ggdb -Wall -Wextra")
	set( CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra")

	if(Optimize)
		message(STATUS "Optimization: OFF.. (DEBUG IS ON)")
	endif(Optimize)
else(Debug)
	add_definitions(-DNDEBUG)

	set( CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -Wall")
	set( CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -Wall")

	if(Optimize)
		message(STATUS "Optimization: ON..")

		set( CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -march=native -O3 -pipe -fomit-frame-pointer")
		set( CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -march=native -O3 -pipe -fomit-frame-pointer")
	endif(Optimize)
endif(Debug)

if(DebugMake)
	SET (CMAKE_VERBOSE_MAKEFILE 1) # Use 1 for debugging, 0 for release
endif(DebugMake)

if(Profile)
	message(STATUS "Profiling: ON...")

	set( CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -pg")
	set( CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -pg")
endif(Profile)

if(C++11)
	message(STATUS "Enabling C++11 support...")
	set( CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++0x")
endif(C++11)

if(C99)
	message(STATUS "Enabling C99 support...")
	set( CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -std=c99")
endif(C99)

#
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (PLUGIN_OUTPUT_PATH "${MAINFOLDER}/bin/plugins")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/bin/lib")
SET (ARCHIVE_OUTPUT_PATH "${MAINFOLDER}/bin/lib/static")

SET (PLUGIN_PREFIX "plugin_")

#
# Project Search Paths
#
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")
LIST (APPEND CMAKE_MODULE_PATH "${MAINFOLDER}/thirdparty/share/cmake")

INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

#
# Locate Project Prerequisites
#

#
# BOOST
#
# FIND_PACKAGE (Boost 1.46.1 COMPONENTS "date_time" "filesystem" "graph" "iostreams" "program_options" "regex" "serialization" "signals" "system" "thread" "wserialization" REQUIRED)
FIND_PACKAGE (Boost 1.48 COMPONENTS program_options thread REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

#
# QT4
#
# FIND_PACKAGE (Qt4 REQUIRED)
# INCLUDE(UseQt4)

#
# Log4Cxx
#
# FIND_PACKAGE (Log4Cxx REQUIRED)
# INCLUDE_DIRECTORIES(${Log4Cxx_INCLUDE_DIRS})
# LINK_DIRECTORIES(${Log4Cxx_LIBRARY_DIRS})

#
# UnitTest++
#
# FIND_PACKAGE (UnitTestPlusPlus REQUIRED)
# INCLUDE_DIRECTORIES(${UnitTestPlusPlus_INCLUDE_DIRS})
# LINK_DIRECTORIES(${UnitTestPlusPlus_LIBRARY_DIRS})

#
# libircclient
#

FIND_PACKAGE (libircclient REQUIRED)
INCLUDE_DIRECTORIES(${libircclient_INCLUDE_DIRS})
LINK_DIRECTORIES(${libircclient_LIBRARY_DIRS})

#
# Configure Files
#

CONFIGURE_FILE("${MAINFOLDER}/src/info.h.in" "${MAINFOLDER}/src/info.h")

#
# Add Build Targets
#
ADD_SUBDIRECTORY(thirdparty/logging)
INCLUDE_DIRECTORIES("${MAINFOLDER}/thirdparty/logging")

ADD_SUBDIRECTORY(src)

if(Testing)
	ADD_SUBDIRECTORY(test)
endif(Testing)

#
# Add Install Targets
#
IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
	INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

#
# Add Documentation Targets
#
# INCLUDE (DocumentationTargets)
