/// @file main_controller.c

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

/**
 * @enum game_state
 * @brief Represents the current state of the game.
 */
enum game_state {
  QUIT,          ///< The game was closed
  MAIN_MENU,     ///< The game is on the main menu
  GAME,          ///< The game is on the arena
  GAME_OVER_MENU ///< The game is on the game over menu
};

/**
 * @brief Processes a game frame.
 * 
 * If the @ref game_state is on a menu, call process_menu(), else call process_game(). <br>
 * After processing the input events, 
 * 
 * @param arena A pointer to the arena where the frame will be processed
 * @return 1 if the player died and thus the game ended, 0 otherwise
 */
int (process_frame)();
enum game_state (get_game_state)();
void (set_game_state)(enum game_state state);
unsigned long (get_current_frame)();

int (setup_game)();
int (clean_game)();

#endif /*_MAIN_CONTROLLER_PROJ_H_ */
