#include "entity.h"

const double COS45 = 0.70710678118;


bool (is_idle)(entity* entity) {
  return entity->speed_x == 0 && entity->speed_y == 0;
}

entity* (create_entity)(uint32_t n_sprites, animation* animations) {
  entity* new_entity = (entity*)malloc(sizeof(entity));

  new_entity->pos_x = 0;
  new_entity->pos_y = 0;
  new_entity->speed_x = 0;
  new_entity->speed_y = 0;
  new_entity->health = 0;
  new_entity->idle_front = true;
  new_entity->n_sprites = n_sprites;
  new_entity->animations = animations;

  return new_entity;
}

entity* (create_entity_full)(double pos_x, double pos_y, double speed_x, double speed_y, uint32_t health, uint32_t n_sprites, animation* animations) {
  entity* new_entity = (entity*)malloc(sizeof(entity));

  new_entity->pos_x = pos_x;
  new_entity->pos_y = pos_y;
  new_entity->speed_x = speed_x;
  new_entity->speed_y = speed_y;
  new_entity->idle_front = true;
  new_entity->health = health;
  new_entity->n_sprites = n_sprites;
  new_entity->animations = animations;

  return new_entity;
}

int (destroy_entity)(entity* entity) {
  free(entity);
  return 0;
}

void (move_entity)(entity* entity){
  entity->pos_x += entity->speed_y != 0 ? COS45*entity->speed_x : entity->speed_x;
  entity->pos_y += entity->speed_x != 0 ? COS45*entity->speed_y : entity->speed_y;

  /*
  // bound the position inside the background image size (arena size)
  entity->pos_x = MIN(MAX(0, entity->pos_x), game_background_img.width - entity->animations[0].sprites[0]->width);
  entity->pos_y = MIN(MAX(0, entity->pos_y), game_background_img.height - entity->animations[0].sprites[0]->height);
  */

  entity->pos_x = MIN(MAX(0, entity->pos_x), game_background_img.width - 86);
  entity->pos_y = MIN(MAX(0, entity->pos_y), game_background_img.height - 128);
}
