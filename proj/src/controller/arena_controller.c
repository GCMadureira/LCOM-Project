#include "arena_controller.h"


static unsigned long last_auto_attack = 0;
static unsigned long last_ranged_attack = 0;

void (setup_arena_controller)() {
  last_auto_attack = 0;
  last_ranged_attack = 0;
}

void (handle_ranged_attack)(arena* arena) {
  if (get_current_frame() - last_ranged_attack >= 180) {
    double speed_x = arena->mouse->pos_x - arena->player->pos_x + arena->pos_x;
    double speed_y = arena->mouse->pos_y - arena->player->pos_y + arena->pos_y;

    double lenght = sqrt(speed_x * speed_x + speed_y * speed_y); 
    if(lenght == 0) return ;
    double scale = 5/lenght;

    attack* new_attack = attack_create_full(arena->player->pos_x, arena->player->pos_y, -scale*speed_x, -scale*speed_y, 50, 240, khopesh_attack_animation);

    attack_list_add(&(arena->player_attacks), new_attack);

    last_ranged_attack = get_current_frame();
  }
}

// Handle the auto attack with a cooldown
void (handle_auto_attack)(arena* arena) {
  if (get_current_frame() - last_auto_attack >= 120) {
    double attack_x = arena->player->speed_x > 0 ? 
    arena->player->pos_x + arena->player->animations->sprites[0]->width + 5 :
    arena->player->pos_x - khopesh_attack_animation.sprites[0]->width - 5;

    double attack_y = arena->player->pos_y + arena->player->animations->sprites[0]->height/2 -  khopesh_attack_animation.sprites[0]->height/2;

    attack* new_attack = attack_create_full(attack_x, attack_y, 0, 0, 50, 24, khopesh_attack_animation);

    attack_list_add(&(arena->player_attacks), new_attack);

    last_auto_attack = get_current_frame();
  }
}

int (arena_process_frame)(arena* arena) {
  // If enemies_check_collisions() returns true, the player has collided with an enemy
  if (enemies_check_collisions(arena)) {
    return 1;
  }

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
