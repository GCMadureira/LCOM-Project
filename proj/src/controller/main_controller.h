/** 
 * @file main_controller.h
 * @brief Header file for @ref main_controller.c
 * 
 * This file declares all the functions to be used on the program's higher level logic.
 */

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
 * If the @ref game_state is on a menu, calls process_menu(), else calls process_game(). <br>
 * After processing the input events, it calls arena_process_frame() if the @ref game_state is on the arena and calls game_over_menu() if the player reaches 0 health. <br>
 * At the end, draws the menu or arena, depending on which is active.
 * 
 * @return 0 in case of success, 1 otherwise
 */
int (process_frame)();

/**
 * @brief Getter for the @ref game_state static member.
 * 
 * @return The game_state of the program
 */
enum game_state (get_game_state)();

/**
 * @brief Setter for the @ref game_state static member.
 * 
 * @param state The new state to be set
 */
void (set_game_state)(enum game_state state);

/**
 * @brief Getter for the @ref frame static member.
 * 
 * @return The current frame of the game
 */
unsigned long (get_current_frame)();

/**
 * @brief Sets up the program
 * 
 * Calls static_images_load() and animations_load() to load the xpm assets.
 * It then creates the main menu to start the game.
 * 
 * @return 0 in case of succes, 1 otherwise
 */
int (setup_game)();

/**
 * @brief Cleans up the program
 * 
 * Calls events_clear() and animations_clean() to release the dynamically allocated memory.
 * It then destroys the @ref active_menu and @ref active_arena.
 * 
 * @return 0 in case of succes, 1 otherwise
 */
int (clean_game)();

#endif /*_MAIN_CONTROLLER_PROJ_H_ */
