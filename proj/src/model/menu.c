#include "menu.h"


int (menu_select_option_up)(menu* menu){
  menu->menu_status = (menu->menu_status - 1) >= 0 ? menu->menu_status - 1 : menu->num_options - 1;
  return 0;
}

int (menu_select_option_down)(menu* menu){
  menu->menu_status = (menu->menu_status + 1)%menu->num_options;
  return 0;
}

menu* (menu_create_main)() {
  menu* main_menu = (menu*)malloc(sizeof(menu));

  main_menu->menu_status = 0;
  main_menu->num_options = 2;
  main_menu->sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 2);
  main_menu->sprites[0] = &start_selected_img;
  main_menu->sprites[1] = &quit_selected_img;

  return main_menu;
}

int (menu_destroy)(menu* menu){
  free(menu->sprites);
  free(menu);
  return 0;
}
