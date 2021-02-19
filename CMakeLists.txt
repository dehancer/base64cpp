cmake_minimum_required(VERSION 3.12)

#
# Project
#
set(PROJECT_LIB base64cpp)
project(${PROJECT_LIB} VERSION 1.1.2)

set (VERSION_FILE "version.txt")
file (WRITE "${VERSION_FILE}" "${PROJECT_NAME} ${PROJECT_VERSION}")

#
# Options
#
option(BUILD_TESTING "Enable creation of Eigen tests." OFF)
option(DEHANCER_TARGET_ARCH "")

if (DEHANCER_TARGET_ARCH)
    #
    # x86_64-apple-macos10.13
    # or
    # arm64-apple-macos11
    #
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target ${DEHANCER_TARGET_ARCH}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target ${DEHANCER_TARGET_ARCH}")
endif ()

#
# CXX 11
#
set (CMAKE_CXX_STANDARD 11)
set (BUILD_SHARED_LIBS OFF)

# googletes, etc
set (EXTERNAL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)
set (EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
set (EXTERNAL_INCLUDE_DIR ${EXTERNAL_INSTALL_LOCATION}/include)

#
# Packages
#
find_package(PkgConfig QUIET)

if(NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "pkg-config not found!" )
    message(FATAL_ERROR "sudo apt-get install pkg-config, or brew install pkg-config")
endif()

#
# Programms
#
find_program(CCACHE_FOUND ccache)
find_program(MAKE_EXE NAMES gmake nmake make)

#
# CCache settings
#
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

#
# Includes
#
include(ExternalProject)

#

add_subdirectory(lib)

if(BUILD_TESTING)
    # Google Test
    #
    #
    # Google TEST
    #
    find_package(GTest)
    if (NOT GTEST_FOUND)
        ExternalProject_Add(googletest
                GIT_REPOSITORY https://github.com/google/googletest
                CMAKE_ARGS
                -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
                -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
                -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}
                -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
                )
        set(COMMON_DEPENDENCIES ${COMMON_DEPENDENCIES};googletest)

        include_directories(
                ./
                ../include
                ${CMAKE_BINARY_DIR}/external/include
        )

        link_directories(
                ${CMAKE_BINARY_DIR}/external/lib
        )

    endif()

    add_subdirectory(tests)
    enable_testing ()
endif()

# Install package
#
if (NOT CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR  lib)
endif ()
if (NOT CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR  include)
endif ()

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "\${prefix}")
set(libdir "\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}")
set(includedir "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")

configure_file(${CMAKE_SOURCE_DIR}/base64cpp.pc.in ${CMAKE_CURRENT_BINARY_DIR}/base64cpp.pc @ONLY)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/base64cpp.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
        )

