#ifndef _ARENA_PROJ_H_
#define _ARENA_PROJ_H_

#include <lcom/lcf.h>

#include "entity.h"
#include "structs.h"
#include "../events/events.h"
#include "../drivers/graphics.h"
#include "../controller/main_controller.h"


int (draw_arena)(arena* arena);
arena* (create_arena)();
int (destroy_arena)(arena* arena);
int (move_entities)(arena* arena);


#endif /*_ARENA_PROJ_H_*/
