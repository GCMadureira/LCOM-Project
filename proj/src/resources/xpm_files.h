#ifndef _XPM_FILES_PROJ_H_
#define _XPM_FILES_PROJ_H_

#include <lcom/lcf.h>

xpm_image_t sprite_img;
extern xpm_image_t sprite_img;
xpm_image_t game_background_img;
extern xpm_image_t game_background_img;
xpm_image_t background_img;
extern xpm_image_t background_img;
xpm_image_t start_selected_img;
extern xpm_image_t start_selected_img;
xpm_image_t quit_selected_img;
extern xpm_image_t quit_selected_img;

// Player idle animation frames
xpm_image_t pharaoh_idle_frame0_img;
extern xpm_image_t pharaoh_idle_frame0_img;
xpm_image_t pharaoh_idle_frame1_img;
extern xpm_image_t pharaoh_idle_frame1_img;
xpm_image_t pharaoh_idle_frame2_img;
xpm_image_t pharaoh_idle_frame3_img;
extern xpm_image_t pharaoh_idle_frame3_img;

int (loadAllXpm)();

#endif /*_XPM_FILES_PROJ_H */
