#ifndef _MAIN_VIEWER_PROJ_H_
#define _MAIN_VIEWER_PROJ_H_

#include <lcom/lcf.h>
#include "animations.h"
#include "../controller/main_controller.h"
#include "../model/structs.h"

int (draw_arena)(arena* arena);
int (draw_menu)(menu* menu);
//to draw an entity inside the arena
int (draw_enemies)(arena* arena);
int (draw_attacks)(arena* arena);


#endif /* _MAIN_VIEWER_PROJ_H_ */
