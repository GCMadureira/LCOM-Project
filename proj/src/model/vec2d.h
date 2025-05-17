#ifndef _VEC2D_PROJ_H_
#define _VEC2D_PROJ_H_

#include <lcom/lcf.h>

typedef struct {
  int32_t x, y;
} vec2d;

vec2d (vec2d_add)(vec2d left, vec2d right);
void (vec2d_add_to)(vec2d* left, vec2d right);

vec2d (vec2d_scale)(vec2d vec, int scalar);
void (vec2d_scale_to)(vec2d* vec, int scalar);

#endif /*_VEC2D_PROJ_H_*/
