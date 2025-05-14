#include "vec2d.h"

vec2d (vec2d_add)(vec2d left, vec2d right) {
  return (vec2d){left.x + right.x, left.y + right.y};
}

void (vec2d_add_to)(vec2d* left, vec2d right) {
  left->x += right.x;
  left->y += right.y;
}

vec2d (vec2d_scale)(vec2d vec, int scalar) {
  return (vec2d){vec.x * scalar, vec.y * scalar};
}

void (vec2d_scale_to)(vec2d* vec, int scalar) {
  vec->x *= scalar;
  vec->y *= scalar;
}
