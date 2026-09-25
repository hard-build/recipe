# hard recipes

This repository contains reusable recipes for building compiled C and C++
libraries with [hard](https://github.com/hard-build/hard). Each library has a
standalone `<library>.hard` YAML recipe and a `<library>.hard.h` C++ wrapper
that includes its public headers.

Recipes build static libraries from source and keep downloaded sources,
packages, and build artifacts outside the consuming project. This format
requires the updated hard backend with standalone recipe/dependency support;
older backends that only understand embedded `hard.recipe.v1` comments cannot
read these recipes. The migration does not retain the embedded format.

## Available recipes

| Library | Version | Recipe | Wrapper | Recipe dependencies |
| --- | --- | --- | --- | --- |
| CRC32C | 1.1.2 | [crc32c.hard](crc32c.hard) | `crc32c.hard.h` | — |
| libpng | 1.6.58 | [libpng.hard](libpng.hard) | `libpng.hard.h` | zlib |
| SDL3 (draft) | 3.4.16 | [sdl3.hard](sdl3.hard) | `sdl3.hard.h` | Platform graph pending |
| TinyXML2 | 11.0.0 | [tinyxml2.hard](tinyxml2.hard) | `tinyxml2.hard.h` | — |
| yaml-cpp | 0.9.0 | [yaml-cpp.hard](yaml-cpp.hard) | `yaml-cpp.hard.h` | — |
| zlib | 1.3.2 | [zlib.hard](zlib.hard) | `zlib.hard.h` | — |

Upstream repositories, revisions and checksums are recorded in [hard.yaml](hard.yaml).
The SDL3 draft remains available, but its Linux platform dependencies and the
SDL3_image, SDL3_ttf and SDL3_mixer graph are a later step. They are intended to
be built through recipes too; the draft currently still uses available host
packages for optional backends.

## Usage

Include a wrapper through hard's well-known recipe namespace:

```cpp
#include <recipe/libpng.hard.h>
```

The `recipe/` prefix maps to `github.com/hard-build/recipe/`. An active include
loads the neighboring `.hard` recipe, obtains its upstream sources and
transitive recipe dependencies, builds static packages, adds their installed
include directories, and links their archives into reachable binaries.

## Recipe dependencies

A recipe can refer directly to other descriptors. The libpng example uses:

```yaml
version: 1
source: "github.com/pnggroup/libpng"
build_system: "cmake"
source_directory: "."
dependencies:
  - "zlib.hard"
# See libpng.hard for configure arguments and installed paths.
```

References resolve like quoted includes: the referring recipe's directory,
configured include directories, and the existing GitHub/well-known resolver.
For example, `recipe/zlib.hard` and
`github.com/hard-build/recipe/zlib.hard` are also supported. Recorded revisions,
checksums and project overrides follow the same rules as normal includes.
A direct `.hard` reference does not load an adjacent wrapper.

Alternatively, a wrapper can include a dependent recipe wrapper:

```cpp
#pragma once
#include "zlib.hard.h"
#include <png.h>
```

Both forms can be combined. Only active includes contribute. Cycles are errors;
dependencies build first, and static archives link with dependents before their
dependencies. CMake receives dependency install prefixes through
`CMAKE_PREFIX_PATH` and package metadata paths through `PKG_CONFIG_PATH`.
Consumer exports remain limited to include directories and static archives.
Ambient environment and system search paths remain available to vendor builds.

A package variant includes the recipe, the wrapper's own preprocessed code,
and dependency package variants. Different macro expansions or dependency
graphs select different packages. This also applies to repeated unguarded
includes in one translation unit. Header extensions `.h`, `.hh`, `.hpp` and
`.h++` all select the same neighboring descriptor by removing the final extension.

## Testing

Every recipe has a neighboring `*.test.cpp` GoogleTest source. With the updated
backend, run the complete pinned suite or the dependency pilot:

```bash
hard test --locked .
hard test --locked libpng.test.cpp
```

The libpng test saves and reads RGBA pixels in memory. Its CMake build finds the
zlib package built by hard, and the application links both static archives.
`hard fetch --locked .` downloads and analyzes sources without running CMake
or the compiler. Generated headers required inside a recipe's vendor source
tree are deferred until its build; wrappers need no fetch-specific configuration.
Libpng's CMake build prepares and installs `pnglibconf.h` normally.

## Adding a recipe

Keep recipes in the repository root without per-library directories. Add:

- `<library>.hard`, with `version: 1`, source/build settings and any dependencies;
- `<library>.hard.h`, with ordinary C++ includes and any wrapper code;
- `<library>.test.cpp`, with a focused build, link and runtime test;
- the upstream revision and checksum in `hard.yaml`.

Before submitting a recipe, run its test independently and then the complete
suite. The current recipe build system is CMake with installed static archives.

## License

This repository is available under the [MIT License](LICENSE).
