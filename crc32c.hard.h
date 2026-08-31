/* clang-format off */
/* hard.recipe.v1
source: "github.com/google/crc32c"
build_system: "cmake"
source_directory: "."
configure_arguments:
  - "-DCMAKE_BUILD_TYPE=Release"
  - "-DBUILD_SHARED_LIBS=OFF"
  - "-DCRC32C_BUILD_TESTS=OFF"
  - "-DCRC32C_BUILD_BENCHMARKS=OFF"
  - "-DCRC32C_USE_GLOG=OFF"
  - "-DCRC32C_INSTALL=ON"
  - "-DCMAKE_INSTALL_LIBDIR=lib"
  - "-DCMAKE_INSTALL_INCLUDEDIR=include"
source_include_directories:
  - "include"
include_directories:
  - "include"
static_libraries:
  - "lib/libcrc32c.a"
*/
/* clang-format on */
#pragma once

#include <crc32c/crc32c.h>
