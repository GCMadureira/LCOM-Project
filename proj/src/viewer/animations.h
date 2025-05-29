#ifndef _ANIMATIONS_PROJ_H_
#define _ANIMATIONS_PROJ_H_

#include <lcom/lcf.h>

#include "../model/entity.h"
#include "../model/structs.h"

// add the others again if needed
enum animation_direction {
  LEFT, 
  RIGHT,
  IDLE_
};

enum animation_direction (entity_get_direction)(entity* entity);
int (animations_load)();
int (animations_clean)();
int (animation_destroy)(animation animation);


//the animations themselves
extern animation* pharaoh_animations;
extern animation* enemy1_animations;
extern animation* enemy2_animations;
extern animation* mummy_animations;

extern animation khopesh_attack_right_animation;
extern animation khopesh_attack_left_animation;
extern animation lightning_attack_animation;


#endif /* _ANIMATIONS_PROJ_H_ */
