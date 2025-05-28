#include "static_images.h"

xpm_image_t game_background_img;
xpm_image_t start_selected_img;
xpm_image_t quit_selected_img;
xpm_image_t cursor_img;
xpm_image_t health_bars[5];

int (static_images_load)() {
  #include "../resources/Static Images/static_images.h"

  if(xpm_load(game_background_xpm, XPM_8_8_8_8, &game_background_img) == NULL) return 1;
  if(xpm_load(start_selected_xpm, XPM_8_8_8_8, &start_selected_img) == NULL) return 1;
  if(xpm_load(quit_selected_xpm, XPM_8_8_8_8, &quit_selected_img) == NULL) return 1;
  if(xpm_load(cursor_xpm, XPM_8_8_8_8, &cursor_img) == NULL) return 1;

  xpm_image_t health_0_img, health_1_img, health_2_img, health_3_img, health_4_img;
  if(xpm_load(health_4_xpm, XPM_8_8_8_8, &health_4_img) == NULL) return 1;
  if(xpm_load(health_3_xpm, XPM_8_8_8_8, &health_3_img) == NULL) return 1;
  if(xpm_load(health_2_xpm, XPM_8_8_8_8, &health_2_img) == NULL) return 1;
  if(xpm_load(health_1_xpm, XPM_8_8_8_8, &health_1_img) == NULL) return 1;
  if(xpm_load(health_0_xpm, XPM_8_8_8_8, &health_0_img) == NULL) return 1;

  health_bars[0] = health_0_img;
  health_bars[1] = health_1_img;
  health_bars[2] = health_2_img;
  health_bars[3] = health_3_img;
  health_bars[4] = health_4_img;

  return 0;
}
