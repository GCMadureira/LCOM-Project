/**
 * @file static_images.h
 * @brief Header file all the static images used in the game
 * 
 * This file declares all the static XPM images used throughout the game,
 * including menu backgrounds, UI elements, and game assets.
 */

#ifndef _STATIC_IMAGES_PROJ_H_
#define _STATIC_IMAGES_PROJ_H_

#include <lcom/lcf.h>

/** @brief Background image for the start menu */
extern xpm_image_t start_background_img;

/** @brief Background image for the main game arena */
extern xpm_image_t game_background_img;

/** @brief Background image for the game over screen */
extern xpm_image_t game_over_background_img;

/** @brief Image for the selected "Start" menu option */
extern xpm_image_t start_selected_img;

/** @brief Image for the selected "Quit" menu option */
extern xpm_image_t quit_selected_img;

/** @brief Image for the selected "Play Again" option in game over screen */
extern xpm_image_t play_again_selected_img;

/** @brief Image for the selected "Back to Menu" option in game over screen */
extern xpm_image_t back_to_menu_selected_img;

/** @brief Image for the mouse cursor */
extern xpm_image_t cursor_img;

/** @brief Array of health bar sprites, indexed by health value (0-4) */
extern xpm_image_t health_bars[5];

/** @brief Array of number sprites for displaying digits 0-9 */
extern xpm_image_t number_sprites[10];

/** @brief Sprite for the double points":" used for time display */
extern xpm_image_t two_points;

/** @brief Text sprite for "High Score:" */
extern xpm_image_t high_score_text;

/** @brief Text sprite for "PR-" */
extern xpm_image_t pr;

/**
 * @brief Loads all of our static xpms into memory
 * This function initializes all the static XPM images used in the game, it is called on game initialization.
 * 
 * @return 0 on success, non-zero on failure
 */
int (static_images_load)();

#endif /* _STATIC_IMAGES_PROJ_H_ */
