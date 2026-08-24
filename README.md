# hard recipes

This repository contains reusable recipes for building compiled C and C++
libraries with [hard](https://github.com/hard-build/hard). Each recipe is a
header containing a `hard.recipe.v1` YAML block and the public header of the
library it provides.

Recipes build static libraries from source and keep downloaded sources,
packages, and build artifacts outside the consuming project.

## Available recipes

| Library | Recipe header | Upstream source |
| --- | --- | --- |
| TinyXML2 | `tinyxml2.hard.h` | `github.com/leethomason/tinyxml2` |
| yaml-cpp | `yaml-cpp.hard.h` | `github.com/jbeder/yaml-cpp` |

## Usage

Include a recipe through hard's well-known recipe namespace:

```cpp
#include <recipe/tinyxml2.hard.h>
```

or:

```cpp
#include <recipe/yaml-cpp.hard.h>
```

The `recipe/` prefix maps to `github.com/hard-build/recipe/`. When the include
is active, hard downloads this repository and the upstream library source,
builds the declared static package, adds its installed include directory to the
translation unit, and links its archive into reachable binaries.

## Testing

Every recipe has a neighboring `*.test.cpp` GoogleTest source. Run the complete
suite with:

```bash
hard test .
```

To use the reproducible container toolchain explicitly:

```bash
hard --target=linux.v1 test .
```

## Adding a recipe

Keep recipes in the repository root without per-library directories. Add both:

- `<library>.hard.h`, containing the recipe and public library include;
- `<library>.test.cpp`, containing a focused GoogleTest that builds, links, and
  exercises the library.

Before submitting a recipe, run its test independently and then run the complete
suite.

## License

This repository is available under the [MIT License](LICENSE).
