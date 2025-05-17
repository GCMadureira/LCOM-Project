#ifndef _MAIN_CONTROLLER_PROJ_H_
#define _MAIN_CONTROLLER_PROJ_H_

#include <lcom/lcf.h>
#include "../model/menu.h"
#include "../events/events.h"
#include "../macros/scancodes.h"

enum game_state {
  QUIT,
  MAIN_MENU,
  GAME
};

int (process_frame)();
enum game_state (get_game_state)();
unsigned long (get_current_frame)();

int (setup_game)();
int (clean_game)();

#endif /*_MAIN_CONTROLLER_PROJ_H_ */
