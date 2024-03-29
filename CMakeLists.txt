cmake_minimum_required(VERSION 3.22)

#
# Project
#
set(PROJECT_LIB base64cpp)
project(${PROJECT_LIB} VERSION 1.2.0)

set (VERSION_FILE "version.txt")
file (WRITE "${VERSION_FILE}" "${PROJECT_NAME} ${PROJECT_VERSION}")

#
# Options
#
option(BUILD_TESTING "Enable creation of Eigen tests." OFF)
option(DEHANCER_TARGET_ARCH "" "")

option(DEHANCER_COMMON_DIR  "")
if (NOT DEHANCER_COMMON_DIR)
    set(DEHANCER_COMMON_DIR ${CMAKE_BINARY_DIR}/tmp)
endif ()

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -EHsc -Wno-deprecated-declarations")
    add_definitions(/MT /DWIN32=1 /D_ITERATOR_DEBUG_LEVEL=0)
    string(TOLOWER  ${CMAKE_BUILD_TYPE} BUILD_TYPE)
    if (${BUILD_TYPE} STREQUAL "debug")
        add_definitions(/MTd)
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -rdynamic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -ffast-math")
endif ()



#
# CXX 11
#
set (CMAKE_CXX_STANDARD 17)
set (BUILD_SHARED_LIBS OFF)

# googletes, etc
set (EXTERNAL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)

#
# Packages
#
find_package(PkgConfig QUIET)

if(NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "pkg-config not found!" )
    message(FATAL_ERROR "sudo apt-get install pkg-config, or brew install pkg-config")
endif()

#
# Programs
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
# Google Test
#
if (BUILD_TESTING)

    find_package(GTest)

    if (NOT GTest_FOUND)

        string(STRIP "${CMAKE_C_FLAGS} -D_ITERATOR_DEBUG_LEVEL=0" C_FLAGS)
        string(STRIP "${CMAKE_CXX_FLAGS} -D_ITERATOR_DEBUG_LEVEL=0" CXX_FLAGS)

        set(CMAKE_OSX_ARCHITECTURES "${CMAKE_OSX_ARCHITECTURES}" CACHE STRING "" FORCE)

        include(FetchContent)

        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG      v1.14.0
                SOURCE_DIR "${CMAKE_BINARY_DIR}/googletest-src"
        )

        FetchContent_GetProperties(googletest)

        if(NOT googletest_POPULATED)
            FetchContent_Populate(googletest)
            add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
        endif()

    endif ()

endif ()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

if (BUILD_TESTING)
    add_subdirectory(tests)
    enable_testing ()
endif ()


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

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/base64cpp.pc.in ${CMAKE_CURRENT_BINARY_DIR}/base64cpp.pc @ONLY)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/base64cpp.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
        )

