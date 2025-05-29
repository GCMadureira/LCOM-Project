#include "arena_controller.h"

static uint32_t arena_game_time = 0; // Time the arena was active in seconds
static uint32_t arena_starting_frame = 0; // Track the frame when the arena was created
static unsigned long last_damage_time = 0; // Track when we last damaged the player
static unsigned long last_auto_attack = 0; // Track when the player last auto attacked
static unsigned long last_ranged_attack = 0; // Track when the player last used a ranged attack

uint32_t (get_arena_starting_frame)() {
  return arena_starting_frame;
}

uint32_t (get_arena_game_time)() {
  return arena_game_time;
}

void (setup_arena_controller)() {
  last_auto_attack = 0;
  last_ranged_attack = 0;
  arena_starting_frame = get_current_frame();
  arena_game_time = 0;
}

void (handle_ranged_attack)(arena* arena) {
  if (get_current_frame() - last_ranged_attack >= 180) {
    attack* new_attack = attack_create_full(
      arena->pos_x + arena->mouse->pos_x - lightning_attack_animation.sprites[0]->width/2, 
      arena->pos_y + arena->mouse->pos_y - lightning_attack_animation.sprites[0]->height/2, 
      0, 0, 1, 56, 
      lightning_attack_animation
    );

    attack_list_add(&(arena->player_attacks), new_attack);

    last_ranged_attack = get_current_frame();
  }
}

// Handle the auto attack with a cooldown
void (handle_auto_attack)(arena* arena) {
  if (get_current_frame() - last_auto_attack >= 120) {
    // if the player is moving right or last moved right, attack on the right, else left
    double attack_x = arena->player->speed_x > 0 || arena->player->last_horizontal_direction ? 
    arena->player->pos_x + arena->player->animations->sprites[0]->width + 5 :
    arena->player->pos_x - khopesh_attack_right_animation.sprites[0]->width - 5;

    double attack_y = arena->player->pos_y + arena->player->animations->sprites[0]->height/2 -  khopesh_attack_right_animation.sprites[0]->height/2;

    animation animation = arena->player->speed_x > 0 || arena->player->last_horizontal_direction ? 
    khopesh_attack_right_animation : 
    khopesh_attack_left_animation;

    attack* new_attack = attack_create_full(attack_x, attack_y, 0, 0, 1, 24, animation);

    attack_list_add(&(arena->player_attacks), new_attack);

    last_auto_attack = get_current_frame();
  }
}

int (arena_process_frame)(arena* arena) {
  // If enemies_check_collisions() returns true, the player has collided with an enemy
  if (enemies_check_collisions(arena)) {
    // Add a damage cooldown of 60 frames (1 second at 60 FPS)
    if (get_current_frame() - last_damage_time >= 60) {
      arena->player->health--;
      if (arena->player->health > 0)
        last_damage_time = get_current_frame();
      else
        return 1;
    }
  }

  // update the active time
  if ((get_current_frame() - arena_starting_frame) % 60 == 0)
    ++arena_game_time;

  // spawn the enemies
  handle_enemy_spawning(arena);
  handle_auto_attack(arena);
  
  // move everything
  arena_move_entities(arena);
  return 0;
}

static int (attacks_move)(arena* arena) {
  attack_node* current_attack = arena->player_attacks;
  attack_node* previous_attack = NULL;
  while(current_attack != NULL && current_attack->attack->frames == 0) {
    attack_node* victim = current_attack;
    current_attack = current_attack->next_attack;
    arena->player_attacks = current_attack;
    attack_node_destroy(victim);
  }

  while(current_attack != NULL) {
    attack* attack = current_attack->attack;
    if(attack->frames == 0) {
      previous_attack->next_attack = current_attack->next_attack;
      attack_node_destroy(current_attack);
      current_attack = previous_attack;
    }
    else
      attack_move(attack);
    previous_attack = current_attack;
    current_attack = current_attack->next_attack;
  }

  return 0;
}

int (arena_move_entities)(arena* arena) {
  enemies_move(arena);
  entity_move(arena->player); //move the player
  attacks_move(arena);

  arena->pos_x = arena->player->pos_x - vg_get_hres()/2 + arena->player->animations[0].sprites[0]->width/2;
  arena->pos_y = arena->player->pos_y - vg_get_vres()/2 + arena->player->animations[0].sprites[0]->height/2;
  
  arena->pos_x = MIN(MAX(0, arena->pos_x), game_background_img.width - vg_get_hres());
  arena->pos_y = MIN(MAX(0, arena->pos_y), game_background_img.height - vg_get_vres());
  
  return 0;
}
