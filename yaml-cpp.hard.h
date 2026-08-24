/* clang-format off */
/* hard.recipe.v1
source: "github.com/jbeder/yaml-cpp"
build_system: "cmake"
source_directory: "."
configure_arguments:
  - "-DCMAKE_BUILD_TYPE=Release"
  - "-DYAML_BUILD_SHARED_LIBS=OFF"
  - "-DYAML_CPP_BUILD_CONTRIB=OFF"
  - "-DYAML_CPP_BUILD_TOOLS=OFF"
  - "-DYAML_CPP_BUILD_TESTS=OFF"
  - "-DYAML_CPP_INSTALL=ON"
  - "-DYAML_CPP_FORMAT_SOURCE=OFF"
  - "-DCMAKE_INSTALL_LIBDIR=lib"
  - "-DCMAKE_INSTALL_INCLUDEDIR=include"
source_include_directories:
  - "include"
include_directories:
  - "include"
static_libraries:
  - "lib/libyaml-cpp.a"
*/
/* clang-format on */
#pragma once

#include <yaml-cpp/yaml.h>
