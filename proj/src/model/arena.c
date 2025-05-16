#include "arena.h"

int (draw_arena)(arena* arena) {
  vg_draw_image_section32(0, 0, arena->background_image, arena->position.x, arena->position.y, get_hres(), get_vres()); //draw the visible section of the arena
  vg_draw_image32(arena->player->position.x - arena->position.x, arena->player->position.y - arena->position.y, arena->player->sprites[0]); //draw the player
  return 0;
}

arena* (create_arena)() {
  arena* new_arena = (arena*)malloc(sizeof(arena));
  entity* player = create_entity_full((vec2d){1264 - 43, 1264 - 64}, (vec2d){0,0}, 5, 1, (xpm_image_t*[]){&sprite_img});

  new_arena->position = (vec2d){1264 - 576, 1264 - 432};
  new_arena->player = player;
  new_arena->background_image = &game_background_img;

  return new_arena;
}

int (destroy_arena)(arena* arena) {
  destroy_entity(arena->player);
  free(arena);
  return 0;
}

int (move_entities)(arena* arena) {
  move_entity(arena->player); //move the player

  /*

  vec2d* arena_pos = &(arena->position);
  entity* player = arena->player;

  vec2d arena_speed = player->speed;

  if(player->position.x - arena_pos->x > (int32_t)get_hres()/2 - player->sprites[0]->width/2 && arena_pos->x == game_background_img.width - (int32_t)get_hres()) arena_speed.x = 0; 
  if(player->position.x - arena_pos->x < (int32_t)get_hres()/2 - player->sprites[0]->width/2 && arena_pos->x == 0) arena_speed.x = 0;
  if(player->position.y - arena_pos->y > (int32_t)get_vres()/2 - player->sprites[0]->height/2 && arena_pos->y == game_background_img.height - (int32_t)get_vres()) arena_speed.y = 0; 
  if(player->position.y - arena_pos->y < (int32_t)get_vres()/2 - player->sprites[0]->height/2 && arena_pos->y == 0) arena_speed.y = 0;

  vec2d_add_to(&(arena->position), arena_speed); //move the arena
  arena_pos->x = MIN((uint16_t)MAX(0, arena_pos->x), game_background_img.width - get_hres());
  arena_pos->y = MIN((uint16_t)MAX(0, arena_pos->y), game_background_img.height - get_vres());

  */

  arena->position.x = arena->player->position.x - (int32_t)get_hres()/2 + arena->player->sprites[0]->width/2;
  arena->position.y = arena->player->position.y - (int32_t)get_vres()/2 + arena->player->sprites[0]->height/2;

  arena->position.x = MIN((uint16_t)MAX(0, arena->position.x), game_background_img.width - get_hres());
  arena->position.y = MIN((uint16_t)MAX(0, arena->position.y), game_background_img.height - get_vres());

  return 0;
}
