#include <stdbool.h>
#include <stdio.h>

#include "c-macros/variant.h"

// Format helpers
#define ARGS_IDENT(x) x
#define FMT_BOOL "%s"
#define ARGS_BOOL(x) (x) ? "true" : "false"

// A tagged union representing different shapes
#define SHAPE_VARIANT_FOREACH(X, ...)                       \
  X(float, circle_radius, "%g", ARGS_IDENT, __VA_ARGS__)   \
  X(float, square_side, "%g", ARGS_IDENT, __VA_ARGS__)     \
  X(bool, visible, FMT_BOOL, ARGS_BOOL, __VA_ARGS__)

#define LOG_SHAPE(FMT, ...) printf("[shape] " FMT "\n", __VA_ARGS__)

VARIANT_DECLARE(SHAPE_VARIANT_FOREACH, shape_t, LOG_SHAPE)

static float shape_area(shape_t s) {
  switch (s.tag) {
    case shape_t_TAG_circle_radius:
      return 3.14159f * s.circle_radius * s.circle_radius;
    case shape_t_TAG_square_side:
      return s.square_side * s.square_side;
    default:
      return 0;
  }
}

int main(void) {
  shape_t shapes[] = {
      shape_t_circle_radius(5.0f),
      shape_t_square_side(3.0f),
      shape_t_visible(true),
  };

  for (size_t i = 0; i < sizeof(shapes) / sizeof(shapes[0]); i++) {
    shape_t_log(shapes[i]);
    printf("  area = %g\n", shape_area(shapes[i]));
  }

  return 0;
}
