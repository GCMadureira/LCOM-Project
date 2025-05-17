#ifndef _SPRITES_PROJ_H_
#define _SPRITES_PROJ_H_

#include <lcom/lcf.h>
#include <math.h>
#include "../drivers/graphics.h"
#include "../resources/xpm_files.h"


// useful for animation
enum direction {
  UP, UP_RIGHT,
  RIGHT, DOWN_RIGHT,
  DOWN, DOWN_LEFT,
  LEFT, UP_LEFT,
  IDLE_FRONT, IDLE_BACK
};

typedef struct {
  double pos_x, pos_y;
  double speed_x, speed_y;
  bool idle_front;
  uint32_t health;
  uint32_t n_sprites;
  xpm_image_t** sprites;
} entity;

enum direction (get_entity_direction)(entity* entity);
bool (is_idle)(entity* entity);

entity* (create_entity)(uint32_t n_sprites, xpm_image_t** sprites);
entity* (create_entity_full)(double pos_x, double pos_y, double speed_x, double speed_y, uint32_t health, uint32_t n_sprites, xpm_image_t** sprites);
int (destroy_entity)(entity* entity);

void (move_entity)(entity* entity);


#endif /*_SPRITES_PROJ_H_ */
