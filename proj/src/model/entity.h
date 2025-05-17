#ifndef _SPRITES_PROJ_H_
#define _SPRITES_PROJ_H_

#include <lcom/lcf.h>
#include "vec2d.h"
#include "../drivers/graphics.h"
#include "../resources/xpm_files.h"

typedef struct {
  vec2d position, speed;
  uint32_t health;
  uint32_t n_sprites;
  xpm_image_t** sprites;
} entity;

entity* (create_entity)(uint32_t n_sprites, xpm_image_t** sprites);
entity* (create_entity_full)(vec2d position, vec2d speed, uint32_t health, uint32_t n_sprites, xpm_image_t** sprites);
int (destroy_entity)(entity* entity);

void (move_entity)(entity* entity);


#endif /*_SPRITES_PROJ_H_ */
