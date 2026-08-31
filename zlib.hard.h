/* clang-format off */
/* hard.recipe.v1
source: "github.com/madler/zlib"
build_system: "cmake"
source_directory: "."
configure_arguments:
  - "-DCMAKE_BUILD_TYPE=Release"
  - "-DZLIB_BUILD_SHARED=OFF"
  - "-DZLIB_BUILD_STATIC=ON"
  - "-DZLIB_BUILD_TESTING=OFF"
  - "-DZLIB_BUILD_MINIZIP=OFF"
  - "-DZLIB_INSTALL=ON"
  - "-DCMAKE_INSTALL_LIBDIR=lib"
  - "-DCMAKE_INSTALL_INCLUDEDIR=include"
source_include_directories:
  - "."
include_directories:
  - "include"
static_libraries:
  - "lib/libz.a"
*/
/* clang-format on */
#pragma once

#include <zlib.h>
