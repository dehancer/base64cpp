# Base64cpp

## Build and install

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$HOME/local-dehancer"
cmake --build build --config Release --parallel $(nproc)
cmake --install build --config Release
```

Use `-DBUILD_SHARED_LIBS=ON` for a shared library; the default is static.

`GNUInstallDirs` selects subdirectories beneath `CMAKE_INSTALL_PREFIX`: typically
`lib` (or `lib64`) for libraries, `include` for headers, and `bin` for runtime files.
Set `-DCMAKE_INSTALL_LIBDIR=lib` to explicitly select `<prefix>/lib`.
Keep directory overrides relative to preserve prefix overrides and relocation;
absolute directory overrides deliberately bypass the prefix.

## Use an installed package

```cmake
find_package(base64cpp CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE base64cpp::base64cpp)
```

This project is not versioned so no cmake version file is being installed and
consumers should not request particular version in `find_package()`.

Configure the consumer with `-DCMAKE_PREFIX_PATH="$HOME/local-dehancer"`.

To embed in another project: `FetchContent_MakeAvailable(base64cpp)`.

## pkg-config

Disabled by default. Configure with `-DCREATE_PKG_CONFIG=ON` to generate and
install `base64cpp.pc`. The CMake package is always generated and installed.

```sh
export PKG_CONFIG_PATH="$HOME/local-dehancer/lib/pkgconfig"
pkg-config --cflags --libs base64cpp
```

## Tests

Install GoogleTest, then configure with:

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Example

```cpp
#include <base64cpp.hpp>

std::string source = "1234567890binary";
std::string encoded;
base64::encode(source, encoded, 24); // Default line width: 76.

std::string decoded;
base64::decode(encoded, decoded);
```
