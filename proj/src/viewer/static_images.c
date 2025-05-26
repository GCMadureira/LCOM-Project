#include "static_images.h"

xpm_image_t game_background_img;
xpm_image_t start_selected_img;
xpm_image_t quit_selected_img;

int (static_images_load)() {
  #include "../resources/Static Images/static_images.h"

  if(xpm_load(game_background_xpm, XPM_8_8_8_8, &game_background_img) == NULL) return 1;
  if(xpm_load(start_selected_xpm, XPM_8_8_8_8, &start_selected_img) == NULL) return 1;
  if(xpm_load(quit_selected_xpm, XPM_8_8_8_8, &quit_selected_img) == NULL) return 1;

  return 0;
}
