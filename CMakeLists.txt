cmake_minimum_required(VERSION 4.2)

project(base64cpp VERSION 1.3.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(BUILD_TESTING "Build tests" OFF)
option(CREATE_PKG_CONFIG "Generate and install pkg-config metadata" OFF)

add_subdirectory(lib)

set(base64cpp_cmake_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/base64cpp")

configure_package_config_file(
    lib/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/base64cppConfig.cmake"
    INSTALL_DESTINATION "${base64cpp_cmake_install_dir}"
)

install(EXPORT base64cppTargets
    FILE base64cppTargets.cmake
    NAMESPACE base64cpp::
    DESTINATION "${base64cpp_cmake_install_dir}"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/base64cppConfig.cmake"
    DESTINATION "${base64cpp_cmake_install_dir}"
)

if(CREATE_PKG_CONFIG)
    # Express relative install directories through pkg-config's relocatable prefix.
    file(RELATIVE_PATH base64cpp_pc_prefix
        "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig"
        "${CMAKE_INSTALL_PREFIX}"
    )

    set(base64cpp_pc_prefix "\${pcfiledir}/${base64cpp_pc_prefix}")

    foreach(directory IN ITEMS LIBDIR INCLUDEDIR)
        if(IS_ABSOLUTE "${CMAKE_INSTALL_${directory}}")
            set(base64cpp_pc_${directory} "${CMAKE_INSTALL_${directory}}")
        else()
            set(base64cpp_pc_${directory} "\${prefix}/${CMAKE_INSTALL_${directory}}")
        endif()
    endforeach()

    configure_file(base64cpp.pc.in base64cpp.pc @ONLY)

    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/base64cpp.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
    )
endif()

if(PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)

    add_executable(base64-test tests/base64.cpp)
    target_link_libraries(base64-test PRIVATE
        base64cpp::base64cpp
        GTest::gtest_main
    )

    gtest_discover_tests(base64-test)
endif()
