#ifndef _MENU_PROJ_H_
#define _MENU_PROJ_H_

#include <lcom/lcf.h>

#include "../drivers/graphics.h"
#include "../viewer/static_images.h"
#include "structs.h"


int (menu_select_option_up)(menu* menu);
int (menu_select_option_down)(menu* menu);

menu* (menu_create_main)();
int (menu_destroy)(menu* menu);

#endif /*_MENU_PROJ_H_ */
