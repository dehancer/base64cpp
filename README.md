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

Windows pkg-config
=======
    I assume here that MinGW was installed to C:\MinGW. 
    There were multiple versions of the packages available, 
    and in each case I just downloaded the latest version.
    
    go to http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/
    download the file pkg-config_0.26-1_win32.zip
    extract the file bin/pkg-config.exe to C:\MinGW\bin
    download the file gettext-runtime_0.18.1.1-2_win32.zip
    extract the file bin/intl.dll to C:\MinGW\bin
    go to http://ftp.gnome.org/pub/gnome/binaries/win32/glib/2.28
    download the file glib_2.28.8-1_win32.zip
    extract the file bin/libglib-2.0-0.dll to C:\MinGW\bin

Windows GCC
=======

    cmake -G Xcode \ 
    -DCMAKE_TOOLCHAIN_FILE=~/Develop/Dehancer/Dehancer-Plugins/ios-cmake/ios.toolchain.cmake \
    -DPLATFORM=OS64COMBINED \
    -DENABLE_BITCODE=ON \
    -DBUILD_TESTING=OFF \
    -DCMAKE_INSTALL_PREFIX=~/Develop/local/ios/dehancer
    cmake --build . --config Release && cmake --install . --config Release


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

 
  