#include "arena_controller.h"

// Maximum number of enemies that can exist at once
#define MAX_ENEMIES 50

static unsigned long last_enemy_spawn = 0;  // Track when we last spawned an enemy
static unsigned long last_damage_time = 0;  // Track when we last damaged the player

// Handle enemy spawning with a cooldown
static void (handle_enemy_spawning)(arena* arena) {
  // Spawn a new enemy every 120 frames (2 seconds at 60 FPS)
  if (get_current_frame() - last_enemy_spawn >= 120) {
    if (spawn_enemy(arena) == 0) {  // If spawn was successful
      last_enemy_spawn = get_current_frame();
    }
  }
}

int (arena_process_frame)(arena* arena) {
  // If enemies_check_collisions() returns true, the player has collided with an enemy
  if (enemies_check_collisions(arena)) {
    // Add a damage cooldown of 60 frames (1 second at 60 FPS)
    if (get_current_frame() - last_damage_time >= 60) {
      if (arena->player->health > 0) {
        arena->player->health--;
        last_damage_time = get_current_frame();
      }
      return 1;
    }
  }

  // spawn the enemies
  handle_enemy_spawning(arena);

  // move everything
  arena_move_entities(arena);

  return 0;
}

int (arena_move_entities)(arena* arena) {
  enemies_move(arena);
  entity_move(arena->player); //move the player

  arena->pos_x = arena->player->pos_x - vg_get_hres()/2 + arena->player->animations[0].sprites[0]->width/2;
  arena->pos_y = arena->player->pos_y - vg_get_vres()/2 + arena->player->animations[0].sprites[0]->height/2;
  
  arena->pos_x = MIN(MAX(0, arena->pos_x), game_background_img.width - vg_get_hres());
  arena->pos_y = MIN(MAX(0, arena->pos_y), game_background_img.height - vg_get_vres());
  
  return 0;
}
