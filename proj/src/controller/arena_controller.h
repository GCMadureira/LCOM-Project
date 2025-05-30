#ifndef _ARENA_CONTROLLER_PROJ_H_
#define _ARENA_CONTROLLER_PROJ_H_

#include <lcom/lcf.h>
#include "../model/structs.h"
#include "../model/entity.h"
#include "../model/arena.h"
#include "../model/attack.h"
#include "main_controller.h"
#include "enemy_controller.h"

uint32_t (get_arena_game_time)();
uint32_t (get_arena_starting_frame)();
uint32_t (get_high_score)();
void (update_high_score)(uint32_t new_time);
void (handle_ranged_attack)(arena* arena);
void (handle_auto_attack)(arena* arena);
int (arena_move_entities)(arena* arena);
int (arena_process_frame)(arena* arena);
void (setup_arena_controller)();

#endif /*_ARENA_CONTROLLER_PROJ_H_ */
