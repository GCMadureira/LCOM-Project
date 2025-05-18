#ifndef _SPRITES_PROJ_H_
#define _SPRITES_PROJ_H_

#include <lcom/lcf.h>
#include <math.h>

#include "../drivers/graphics.h"
#include "../viewer/animations.h"
#include "../viewer/static_images.h"
#include "structs.h"


bool (is_idle)(entity* entity);

entity* (create_entity)(uint32_t n_sprites, animation* animations);
entity* (create_entity_full)(double pos_x, double pos_y, double speed_x, double speed_y, uint32_t health, uint32_t n_sprites, animation* animations);
int (destroy_entity)(entity* entity);

void (move_entity)(entity* entity);


#endif /*_SPRITES_PROJ_H_ */
