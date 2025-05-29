#ifndef _MAIN_CONTROLLER_PROJ_H_
#define _MAIN_CONTROLLER_PROJ_H_

#include <lcom/lcf.h>

#include "../model/menu.h"
#include "../model/arena.h"
#include "../events/events.h"
#include "../macros/scancodes.h"
#include "../viewer/static_images.h"
#include "../viewer/main_viewer.h"
#include "enemy_controller.h"
#include "arena_controller.h"

enum game_state {
  QUIT,
  MAIN_MENU,
  GAME
};

extern arena* active_arena;

int (process_frame)();
enum game_state (get_game_state)();
void (set_game_state)(enum game_state state);
unsigned long (get_current_frame)();
void (reset_game_time)();

int (setup_game)();
int (clean_game)();

#endif /*_MAIN_CONTROLLER_PROJ_H_ */
