#include "main_viewer.h"
#include <stdio.h>

static const uint8_t ANIMATION_SPEED = 8;

int (draw_arena)(arena* arena) {
  //draw the visible section of the arena
  vg_draw_image_section32(0, 0, arena->background_image, arena->pos_x, arena->pos_y, vg_get_hres(), vg_get_vres());

  // Draw all active enemies
  draw_enemies(arena);

  //draw the player
  animation animation = arena->player->animations[entity_get_direction(arena->player)];
  vg_draw_image32(arena->player->pos_x - arena->pos_x, arena->player->pos_y - arena->pos_y, animation.sprites[(get_current_frame()%(animation.n_frames * ANIMATION_SPEED))/ANIMATION_SPEED]);

  // Draw all active attacks
  draw_attacks(arena);

  // Draw all active hearts
  draw_hearts(arena);

  //draw the mouse
  vg_draw_image32(arena->mouse->pos_x, arena->mouse->pos_y, &cursor_img);
  
  // Get health bar image based on player's health (0-4)
  int health_status = arena->player->health;

  vg_draw_image32(10, vg_get_vres() - health_bars[health_status].height - 10, &(health_bars[health_status]));

  //draw the mouse
  vg_draw_image32(arena->mouse->pos_x, arena->mouse->pos_y, &cursor_img);

  // Draw timer in mins:seconds format
  unsigned long time = get_arena_game_time();
  int minutes = time / 60;
  int seconds = time % 60;
  
  // Draw minutes
  // Pos (10,10)
  vg_draw_image32(10, 10, &number_sprites[minutes / 10]);
  // Pos (10 + sprite width, 10)
  vg_draw_image32(10 + number_sprites[0].width, 10, &number_sprites[minutes % 10]);
  
  // Draw the ":" | Pos (150, 10)
  vg_draw_image32(10 + number_sprites[0].width * 2, 10, &two_points); 
  
  // Draw seconds
  // Pos (10 + sprite width*3, 10)
  vg_draw_image32(10 + number_sprites[0].width * 3, 10, &number_sprites[seconds / 10]);
  // Pos (10 + sprite width*4, 10)
  vg_draw_image32(10 + number_sprites[0].width * 4, 10, &number_sprites[seconds % 10]);
  
  return 0;
}

// Draw all active enemies
int (draw_enemies)(arena* arena) {
  entity_node* current_enemy = arena->enemies;
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


int (draw_attacks)(arena* arena) {
  attack_node* current_attack = arena->player_attacks;
  while(current_attack != NULL) {
    attack* attack = current_attack->attack;
    animation animation = attack->animation;
    
    vg_draw_image32(
        attack->pos_x - arena->pos_x,
        attack->pos_y - arena->pos_y,
        animation.sprites[animation.n_frames - 1 - ((attack->frames % (animation.n_frames * ANIMATION_SPEED))  / ANIMATION_SPEED)]
    );

    current_attack = current_attack->next_attack;
  }
  return 0;
}

int (draw_hearts)(arena* arena) {
  entity_node* current_heart = arena->hearts;
  while(current_heart != NULL) {
    entity* heart = current_heart->entity;
    
    // Draw the heart relative to the arena's position
    vg_draw_image32(
        heart->pos_x - arena->pos_x,
        heart->pos_y - arena->pos_y,
        heart->animations[0].sprites[(get_current_frame() % (heart->animations[0].n_frames * ANIMATION_SPEED)) / ANIMATION_SPEED]
    );

    current_heart = current_heart->next_entity;
  }
  return 0;
}

int (draw_menu)(menu* menu){
  if(menu->background_image != NULL) vg_draw_image32(0, 0, menu->background_image);
  vg_draw_image32(0, 0, menu->sprites[menu->menu_status]);
  return 0;
}
