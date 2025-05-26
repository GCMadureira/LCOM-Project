#ifndef _SPRITES_PROJ_H_
#define _SPRITES_PROJ_H_

#include <lcom/lcf.h>
#include <math.h>

#include "../drivers/graphics.h"
#include "../viewer/animations.h"
#include "../viewer/static_images.h"
#include "structs.h"


bool (entity_is_idle)(entity* entity);

entity* (entity_create)(uint32_t n_sprites, animation* animations);
entity* (entity_create_full)(double pos_x, double pos_y, double speed_x, double speed_y, double speed_multiplier, uint32_t health, uint32_t n_sprites, animation* animations);
int (entity_destroy)(entity* entity);

void (entity_move)(entity* entity);

entity_list* (entity_list_create)();
void (entity_list_add)(entity_list* list, entity* entity);
void (entity_list_destroy)(entity_list* list);

#endif /*_SPRITES_PROJ_H_ */
