# c-macros

Two header-only C files built on X-macros. `enum.h` declares an enum together with a function that returns each value's name as a string. `variant.h` declares a tagged union, similar to a Rust enum with data, with a constructor per member and a log function.

Written in 2021; cleaned up and given examples in 2026.

## enum.h

```c
#include "c-macros/enum.h"

#define COLOR_ENUM_FOREACH(X, ...) \
  X(COLOR_RED, __VA_ARGS__)       \
  X(COLOR_GREEN, __VA_ARGS__)     \
  X(COLOR_BLUE, __VA_ARGS__)

ENUM_DECLARE(COLOR_ENUM_FOREACH, color_t)

// color_t_get_str(COLOR_GREEN) returns "COLOR_GREEN"
```

## variant.h

```c
#include "c-macros/variant.h"

#define ARGS_IDENT(x) x

#define SHAPE_VARIANT_FOREACH(X, ...)                     \
  X(float, circle_radius, "%g", ARGS_IDENT, __VA_ARGS__) \
  X(float, square_side, "%g", ARGS_IDENT, __VA_ARGS__)

#define LOG_SHAPE(FMT, ...) printf("[shape] " FMT "\n", __VA_ARGS__)

VARIANT_DECLARE(SHAPE_VARIANT_FOREACH, shape_t, LOG_SHAPE)

// shape_t s = shape_t_circle_radius(5.0f);
// s.tag == shape_t_TAG_circle_radius
// shape_t_log(s) prints "[shape] circle_radius=5"
```

Each entry takes the member type, its name, a printf format and a macro that turns the value into printf arguments. The full examples are in `examples/`.

## Use

Copy `enum.h` and `variant.h` into a `c-macros/` folder on your include path. The examples include them as `c-macros/enum.h`, so from a clone named `c-macros`:

```sh
cc -std=c11 -I.. examples/enum_example.c -o enum-example
./enum-example
```

With Nix:

```sh
nix build .#enum-example && ./result/bin/enum-example
nix build .#variant-example && ./result/bin/variant-example
nix build          # installs the headers to result/include/c-macros/
```

## Status

Small and finished. No further work planned.

## License

0BSD. See `LICENSE`.
