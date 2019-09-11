# Base64cpp

 Base64 with encoding new line C++11 binary to ascii string encoder and decoder library.
 
 ## Requirements
 1. c++11
 1. cmake
 1. gcc/clang
 
 ## Build
 
     $ git clone https://github.com/dnevera/base64cpp
     $ cd ./base64cpp; mkdir build; cd ./build
     $ cmake ..; make -j4 install

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

 
  