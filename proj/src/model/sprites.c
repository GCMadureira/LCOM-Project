#include "sprites.h"

entity* (create_entity)(uint32_t n_sprites, xpm_image_t** sprites) {
  entity* new_entity = (entity*)malloc(sizeof(entity));

  new_entity->position = (vec2d){0,0};
  new_entity->speed = (vec2d){0,0};
  new_entity->health = 0;
  new_entity->n_sprites = n_sprites;
  new_entity->sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * n_sprites);
  for(uint32_t i = 0; i < n_sprites; ++i) new_entity->sprites[i] = sprites[i];

  return new_entity;
}

entity* (create_entity_full)(vec2d position, vec2d speed, uint32_t health, uint32_t n_sprites, xpm_image_t** sprites){
  entity* new_entity = (entity*)malloc(sizeof(entity));

  new_entity->position = position;
  new_entity->speed = speed;
  new_entity->health = health;
  new_entity->n_sprites = n_sprites;
  new_entity->sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * n_sprites);
  for(uint32_t i = 0; i < n_sprites; ++i) new_entity->sprites[i] = sprites[i];

  return new_entity;
}

int (destroy_entity)(entity* entity) {
  free(entity->sprites);
  free(entity);
  return 0;
}

void (move_entity)(entity* entity){
  vec2d_add_to(&(entity->position), entity->speed);
}

int (draw_entity)(entity* entity){
  return vg_draw_image32(entity->position.x, entity->position.y, entity->sprites[0]);
}
