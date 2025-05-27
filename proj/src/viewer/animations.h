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

enum animation_direction (entity_get_direction)(entity* entity);
int (animations_load)();
int (animations_clean)();
int (animation_destroy)(animation animation);


//the animations themselves
extern animation* pharaoh_animations;
extern animation* enemy_animations;

extern animation khopesh_attack_animation;


#endif /* _ANIMATIONS_PROJ_H_ */
