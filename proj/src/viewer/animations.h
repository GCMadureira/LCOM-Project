#ifndef _ANIMATIONS_PROJ_H_
#define _ANIMATIONS_PROJ_H_

#include <lcom/lcf.h>

#include "../model/entity.h"
#include "../model/structs.h"


enum animation_direction {
  UP, UP_RIGHT,
  RIGHT, DOWN_RIGHT,
  DOWN, DOWN_LEFT,
  LEFT, UP_LEFT,
  IDLE_DOWN, IDLE_UP
};

enum animation_direction (get_entity_direction)(entity* entity);
int (load_animations)();
int (clean_animations)();
int (destroy_animation)(animation animation);


//the animations themselves
extern animation* pharaoh_animations;


#endif /* _ANIMATIONS_PROJ_H_ */
