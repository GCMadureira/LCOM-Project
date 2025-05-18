#ifndef _MENU_PROJ_H_
#define _MENU_PROJ_H_

#include <lcom/lcf.h>

#include "../drivers/graphics.h"
#include "structs.h"


int (menu_select_option_up)(menu* menu);
int (menu_select_option_down)(menu* menu);

menu* (create_main_menu)();
int (destroy_menu)(menu* menu);
int (draw_menu)(menu* menu);

#endif /*_MENU_PROJ_H_ */
