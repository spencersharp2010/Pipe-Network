# Spencer Sharp
# pipenetwork c-make file

cmake_minimum_required( VERSION 3.4.3 )

# Project name and programming language
project( PipeNetwork CXX )

# Gather files and store paths in CMake variables
file( GLOB PIPNET_HEADER_FILES pipenetwork/inc/*.h* )
file( GLOB PIPNET_LIBRARY_SOURCE_FILES pipenetwork/src/*.cpp )
file( GLOB PIPNET_TEST_SOURCE_FILES pipenetwork/test/*.cpp )
file( GLOB LINALG_HEADER_FILES linalg/inc/*.h* )
file( GLOB LINALG_TEST_SOURCE_FILES linalg/test/*.cpp )
file( GLOB LINALG_LIBRARY_SOURCE_FILES linalg/src/*.cpp )
file( GLOB DRIVERS_SOURCE_FILES drivers/*.cpp )

# Specify the folders with header files, otherwise our includes are not found
include_directories( pipenetwork/inc )
include_directories( linalg/inc )
include_directories( external/catch )

# Changes the default install path to build/install, assuming build is the project directory
if ( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
    set ( CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "default install path" FORCE )
endif( )

# This will add the install path to the rpath of the installed binaries to make dynamic linking work
SET( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}" )

# Enables exporting all symbols to the dll on windows
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

# When compiling with gcc we need to compile libraries with fPIC (stands for position independent code).
if( CMAKE_COMPILER_IS_GNUCXX )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pedantic -Wall -Werror -std=c++11" )
endif( CMAKE_COMPILER_IS_GNUCXX )

# Add compilation target for our library
add_library( linalg SHARED ${LINALG_LIBRARY_SOURCE_FILES} ${LINALG_HEADER_FILES} )
add_library( pipenetwork SHARED ${PIPNET_LIBRARY_SOURCE_FILES} ${PIPNET_HEADER_FILES} ${LINALG_LIBRARY_SOURCE_FILES} ${LINALG_HEADER_FILES})

# specify the relative path the shared library object shall be installed to

if( WIN32 )
    	install( TARGETS linalg RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} )
    install( TARGETS pipenetwork RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} )
else( )
    	install( TARGETS linalg LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX} )
    install( TARGETS pipenetwork LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX} )
endif( )

# Add test runner
add_executable( linalg_testrunner ${LINALG_TEST_SOURCE_FILES})
target_link_libraries( linalg_testrunner linalg )

add_executable( pipenetwork_testrunner ${PIPNET_TEST_SOURCE_FILES} )
target_link_libraries( pipenetwork_testrunner pipenetwork )

add_executable( driver ${DRIVERS_SOURCE_FILES} ${PIPNET_HEADER_FILES} )
target_link_libraries( driver pipenetwork linalg)

install( TARGETS linalg_testrunner RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} )
install( TARGETS pipenetwork_testrunner RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} )
install( TARGETS driver RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX} )