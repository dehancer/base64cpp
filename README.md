# Base64cpp

 Base64 with encoding new line C++11 binary to ascii string encoder and decoder library.
 
 ## Requirements
 1. c++11
 1. cmake
 1. gcc/clang
 
 ## Build
 
    git clone https://github.com/dnevera/base64cpp
    cd ./base64cpp; mkdir build; cd ./build
    # mac os M1 
    cmake -DDEHANCER_TARGET_ARCH=arm64-apple-macos11 -DBUILD_TESTING=ON ..; make -j4
    # or mac os Intel
    cmake -DDEHANCER_TARGET_ARCH=x86_64-apple-macos10.13 -DBUILD_TESTING=ON ..; make -j4
    # or Linux Intel
    cmake -DBUILD_TESTING=ON ..; make -j4
    make test

Windows GCC
=======

    # mingw
    # Install https://www.msys2.org/
    # https://blog.jetbrains.com/clion/2020/12/setting-up-clang-on-windows/

    pacman -S mingw-w64-x86_64-toolchain
    pacman -S mingw-w64-x86_64-clang
    pacman -S mingw-w64-x86_64-cmake
    pacman -S libcurl
    pacman -S zlib-devel
    pacman -S libcurl-devel


Windows MVSC
=======
    # Requrements: 
    # Visual Studio, English Language Pack!
    # https://vcpkg.info/
    # GitBash

    cd C:
    git clone https://github.com/microsoft/vcpkg
    cd /c/vcpkg/
    ./bootstrap-vcpkg.sh
    /c/vcpkg/vcpkg integrate install
    /c/vcpkg/vcpkg install gtest

    # cmake integration
    -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake

 ## Build in project
 
 ### cmake 
 
 ```cmake 
 
 find_package (PkgConfig QUIET)
 
 # ...
 
 pkg_check_modules(base64cpplib base64cpp)
 
 if (base64cpplib_FOUND)
 
     include_directories(${base64cpplib_INCLUDE_DIRS})
     link_directories(${base64cpplib_LIBRARY_DIRS})
      
 else()
 
     ExternalProject_Add(base64cpplib
             GIT_REPOSITORY https://github.com/dnevera/base64cpp
             CMAKE_ARGS
             -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
             )
 
     add_dependencies(base64cpplib)    
     
 endif()
 
 # ...
 
 target_link_libraries(
         target
         ...
         ${base64cpplib_LIBRARIES}
         ...
 )

 
 ```
 
 ## Examples
 
 ```cpp
 #include <base64cpp.hpp>
 
 //...
 
   std::string source  = "1234567890binary";
   std::string encoded;
   int line_size = 24; // by default 72

   base64::encode(source, encoded, line_size);
   
   std::string decoded;
   
   base64::decode(encoded, decoded);
   
 //...

 ```

 
  