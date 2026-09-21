add_library(base64cpp ../src/base_64_cpp.cpp)
add_library(base64cpp::base64cpp ALIAS base64cpp)

target_compile_features(base64cpp PUBLIC cxx_std_11)

target_sources(base64cpp PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ../include
    FILES ../include/base64cpp.hpp
)

set_target_properties(base64cpp PROPERTIES
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

install(TARGETS base64cpp
    EXPORT base64cppTargets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
