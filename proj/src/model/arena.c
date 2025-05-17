#include "arena.h"

int (draw_arena)(arena* arena) {
  vg_draw_image_section32(0, 0, arena->background_image, arena->pos_x, arena->pos_y, get_hres(), get_vres()); //draw the visible section of the arena
  vg_draw_image32(arena->player->pos_x - arena->pos_x, arena->player->pos_y - arena->pos_y, arena->player->sprites[0]); //draw the player
  return 0;
}

arena* (create_arena)() {
  arena* new_arena = (arena*)malloc(sizeof(arena));
  entity* player = create_entity_full(1264 - 43, 1264 - 64, 0, 0, 5, 1, (xpm_image_t*[]){&sprite_img});

  new_arena->pos_x = 1264 - 576;
  new_arena->pos_y = 1264 - 432;
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

  arena->pos_x = arena->player->pos_x - get_hres()/2 + arena->player->sprites[0]->width/2;
  arena->pos_y = arena->player->pos_y - get_vres()/2 + arena->player->sprites[0]->height/2;
  
  arena->pos_x = MIN(MAX(0, arena->pos_x), game_background_img.width - get_hres());
  arena->pos_y = MIN(MAX(0, arena->pos_y), game_background_img.height - get_vres());
  
  return 0;
}
