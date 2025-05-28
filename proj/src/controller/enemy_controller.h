#ifndef _ENEMY_CONTROLLER_PROJ_H_
#define _ENEMY_CONTROLLER_PROJ_H_

#include <lcom/lcf.h>
#include "../model/structs.h"
#include "../model/entity.h"
#include "../model/arena.h"
#include "main_controller.h"


// Spawn a new enemy offscreen
int (spawn_enemy)(arena* arena);

void (handle_enemy_spawning)(arena* arena);
void (setup_enemy_controller)();

// Returns true if a collision with player occurred
bool (enemies_check_collisions)(arena* arena);

void (enemies_move)(arena* arena);


#endif /*_ENEMY_CONTROLLER_PROJ_H_ */
