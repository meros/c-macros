#include <stdio.h>

#include "c-macros/enum.h"

#define COLOR_ENUM_FOREACH(X, ...) \
  X(COLOR_RED, __VA_ARGS__)       \
  X(COLOR_GREEN, __VA_ARGS__)     \
  X(COLOR_BLUE, __VA_ARGS__)      \
  X(COLOR_YELLOW, __VA_ARGS__)

ENUM_DECLARE(COLOR_ENUM_FOREACH, color_t)

int main(void) {
  color_t colors[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW};

  for (size_t i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
    printf("  %d => %s\n", colors[i], color_t_get_str(colors[i]));
  }

  return 0;
}
