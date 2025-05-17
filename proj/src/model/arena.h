#ifndef _ARENA_PROJ_H_
#define _ARENA_PROJ_H_

#include <lcom/lcf.h>
#include "entity.h"
#include "../events/events.h"
#include "../drivers/graphics.h"
#include "../resources/xpm_files.h"

typedef struct {
  entity* player;
  vec2d position;
  xpm_image_t* background_image;
} arena;

int (draw_arena)(arena* arena);
arena* (create_arena)();
int (destroy_arena)(arena* arena);
int (move_entities)(arena* arena);


#endif /*_ARENA_PROJ_H_*/
