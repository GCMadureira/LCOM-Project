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
  GAME,
  GAME_OVER_MENU
};

extern arena* active_arena;

int (process_frame)();
enum game_state (get_game_state)();
void (set_game_state)(enum game_state state);
unsigned long (get_current_frame)();

int (load_highscore)();
int (save_highscore)();
uint32_t (get_high_score)();
void (update_high_score)(uint32_t new_time);

int (setup_game)();
int (clean_game)();

#endif /*_MAIN_CONTROLLER_PROJ_H_ */
