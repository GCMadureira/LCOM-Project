#include "xpm_files.h"

int (loadAllXpm)() {
  #include "xpm_files.txt"

  if(xpm_load(sprite, XPM_8_8_8_8, &sprite_img) == NULL) return 1;
  if(xpm_load(game_background_xpm, XPM_8_8_8_8, &game_background_img) == NULL) return 1;
  if(xpm_load(background_xpm, XPM_8_8_8_8, &background_img) == NULL) return 1;
  if(xpm_load(start_selected_xpm, XPM_8_8_8_8, &start_selected_img) == NULL) return 1;
  if(xpm_load(quit_selected_xpm, XPM_8_8_8_8, &quit_selected_img) == NULL) return 1;

  return 0;
}
