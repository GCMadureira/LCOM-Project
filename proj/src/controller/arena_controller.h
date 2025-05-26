#ifndef _ARENA_CONTROLLER_PROJ_H_
#define _ARENA_CONTROLLER_PROJ_H_

#include <lcom/lcf.h>
#include "../model/structs.h"
#include "../model/entity.h"
#include "../model/arena.h"
#include "main_controller.h"
#include "enemy_controller.h"


int (arena_move_entities)(arena* arena);
int (arena_process_frame)(arena* arena);


#endif /*_ARENA_CONTROLLER_PROJ_H_ */
