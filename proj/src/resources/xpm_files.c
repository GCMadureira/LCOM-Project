#include "xpm_files.h"

//  XPMs
#include "xpms/background.xpm"
#include "xpms/pharaoh.xpm"
#include "xpms/start_selected.xpm"
#include "xpms/quit_selected.xpm"
#include "xpms/game_background.xpm"

// Player Idle Animation
#include "xpms/pharaoh_idle_frame0.xpm"
#include "xpms/pharaoh_idle_frame1.xpm"
#include "xpms/pharaoh_idle_frame2.xpm"
#include "xpms/pharaoh_idle_frame3.xpm"



int (loadAllXpm)() {

  // Load XPMs
  if(xpm_load(sprite, XPM_8_8_8_8, &sprite_img) == NULL) return 1;
  if(xpm_load(game_background_xpm, XPM_8_8_8_8, &game_background_img) == NULL) return 1;
  if(xpm_load(background_xpm, XPM_8_8_8_8, &background_img) == NULL) return 1;
  if(xpm_load(start_selected_xpm, XPM_8_8_8_8, &start_selected_img) == NULL) return 1;
  if(xpm_load(quit_selected_xpm, XPM_8_8_8_8, &quit_selected_img) == NULL) return 1;

  // Load Idle Player Animation
  if(xpm_load(pharaoh_idle_frame0, XPM_8_8_8_8, &pharaoh_idle_frame0_img) == NULL) return 1;
  if(xpm_load(pharaoh_idle_frame1, XPM_8_8_8_8, &pharaoh_idle_frame1_img) == NULL) return 1;
  if(xpm_load(pharaoh_idle_frame2, XPM_8_8_8_8, &pharaoh_idle_frame2_img) == NULL) return 1;
  if(xpm_load(pharaoh_idle_frame3, XPM_8_8_8_8, &pharaoh_idle_frame3_img) == NULL) return 1;



  return 0;
}
