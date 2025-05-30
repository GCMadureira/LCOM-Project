#ifndef _MENU_PROJ_H_
#define _MENU_PROJ_H_

#include <lcom/lcf.h>

#include "../drivers/drivers.h"
#include "../viewer/static_images.h"
#include "structs.h"


int (menu_select_option_up)(menu* menu);
int (menu_select_option_down)(menu* menu);

menu* (menu_create_main)();
menu* (menu_create_game_over)();

int (menu_destroy)(menu* menu);

#endif /*_MENU_PROJ_H_ */
