#include "enemy_controller.h"

// Spawn a new enemy offscreen
int (spawn_enemy)(arena* arena) {
  // Randomly choose which side of the screen to spawn from
  int side = rand() % 4;  // 0: top, 1: right, 2: bottom, 3: left
  
  double pos_x, pos_y;
  const int SPAWN_OFFSET = 10;  // Distance from arena edge
  
  // Position the enemy offscreen based on the chosen side
  switch (side) {
    case 0: // Top
      // 2528 -> Arena width | 54 -> Enemy width
      pos_x = rand() % (arena->background_image->width - 54);  // Ensure enemy fits within arena width
      pos_y = SPAWN_OFFSET;
      break;
    case 1: // Right
      // 2528 -> Arena width | 87 -> Enemy height
      pos_x = arena->background_image->width - SPAWN_OFFSET;
      pos_y = rand() % (arena->background_image->height - 87);  // Ensure enemy fits within arena height
      break;
    case 2: // Bottom
      // 2528 -> Arena width | 54 -> Enemy width
      pos_x = rand() % (arena->background_image->width - 54);  // Ensure enemy fits within arena width
      pos_y = arena->background_image->height - SPAWN_OFFSET;
      break;
    case 3: // Left
      // 2528 -> Arena width | 87 -> Enemy height
      pos_x = SPAWN_OFFSET;
      pos_y = rand() % (arena->background_image->height - 87);  // Ensure enemy fits within arena height
      break;
  }
  
  // Create the enemy entity with its animations
  entity* new_enemy = entity_create_full(pos_x, pos_y, 0, 0, 2, 100, 8, enemy_animations);
  entity_list_add(arena->enemies, new_enemy);

  return 0;
}

// Check if an enemy collides with the player
static bool (check_collision)(entity* enemy, entity* player) {
  // reduce the hitboxes by 5 pixels to make the collisions more accurate
  // Simple box collision detection | Using correct sprite dimensions
  const double ENEMY_WIDTH = enemy->animations->sprites[0]->width - 5;
  const double ENEMY_HEIGHT = enemy->animations->sprites[0]->height - 5;
  const double PLAYER_WIDTH = player->animations->sprites[0]->width - 5;
  const double PLAYER_HEIGHT = player->animations->sprites[0]->height - 5;

  // Check if the boxes overlap, needs to be improved
  return (enemy->pos_x + 5 < player->pos_x + PLAYER_WIDTH &&
          enemy->pos_x + ENEMY_WIDTH > player->pos_x + 5 &&
          enemy->pos_y + 5 < player->pos_y + PLAYER_HEIGHT &&
          enemy->pos_y + ENEMY_HEIGHT > player->pos_y + 5);
}

// Update all active enemies, move them towards the player and check for collisions
bool (enemies_check_collisions)(arena* arena) {
  entity_node* enemy_node = arena->enemies->first_entity;
  while(enemy_node != NULL) {
    // Check for collision with player
    if (check_collision(enemy_node->entity, arena->player)) {
      return true;  // Collision detected
    }

    enemy_node = enemy_node->next_entity;
  }
  return false;  // No collision
}

void (enemies_move)(arena* arena) {
  entity_node* enemy_node = arena->enemies->first_entity;
  while(enemy_node != NULL) {
    entity* enemy = enemy_node->entity;

    // Calculate direction to player, will be normalized on the move function
    enemy->speed_x = arena->player->pos_x - enemy->pos_x;
    enemy->speed_y = arena->player->pos_y - enemy->pos_y;

    // Move the enemy
    entity_move(enemy);

    enemy_node = enemy_node->next_entity;
  }
}
