#ifndef _STATIC_IMAGES_PROJ_H_
#define _STATIC_IMAGES_PROJ_H_

#include <lcom/lcf.h>

extern xpm_image_t start_background_img;
extern xpm_image_t game_background_img;
extern xpm_image_t game_over_background_img;
extern xpm_image_t start_selected_img;
extern xpm_image_t quit_selected_img;
extern xpm_image_t cursor_img;
extern xpm_image_t health_bars[5];     // Array for the health bar sprites
extern xpm_image_t number_sprites[10]; // Array for number sprites 0-9
extern xpm_image_t two_points;

int (static_images_load)();


#endif /* _STATIC_IMAGES_PROJ_H_ */
