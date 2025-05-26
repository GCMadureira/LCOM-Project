#include "main_viewer.h"

static const uint8_t ANIMATION_SPEED = 8;

int (draw_arena)(arena* arena) {
  //draw the visible section of the arena
  vg_draw_image_section32(0, 0, arena->background_image, arena->pos_x, arena->pos_y, vg_get_hres(), vg_get_vres());

  //draw the player
  animation animation = arena->player->animations[entity_get_direction(arena->player)];
  vg_draw_image32(arena->player->pos_x - arena->pos_x, arena->player->pos_y - arena->pos_y, animation.sprites[(get_current_frame()%(animation.n_frames * ANIMATION_SPEED))/ANIMATION_SPEED]);

  // Draw all active enemies
  draw_enemies(arena);
  
  return 0;
}

// Draw all active enemies
int (draw_enemies)(arena* arena) {
  entity_node* current_enemy = arena->enemies->first_entity;
  while(current_enemy != NULL) {
    // Get the current animation based on the enemy's direction
    entity* enemy = current_enemy->entity;
    animation animation = enemy->animations[entity_get_direction(enemy)];
    
    // Draw the enemy relative to the arena's position
    vg_draw_image32(
        enemy->pos_x - arena->pos_x,
        enemy->pos_y - arena->pos_y,
        animation.sprites[(get_current_frame() % (animation.n_frames * ANIMATION_SPEED)) / ANIMATION_SPEED]
    );

    current_enemy = current_enemy->next_entity;
  }
  return 0;
}

int (draw_menu)(menu* menu){
  vg_draw_image32(0, 0, menu->sprites[menu->menu_status]);
  return 0;
}
