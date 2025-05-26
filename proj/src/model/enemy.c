#include "enemy.h"
#include "arena.h"
#include "../viewer/animations.h"
#include <stdlib.h>
#include <math.h>

// Array to store all enemies
static enemy enemies[MAX_ENEMIES];

// Initialize the enemy array with inactive and undrawn enemies
int init_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].active = false;
        enemies[i].base = NULL;  // Initialize to NULL
    }
    return 0;
}

// Spawn a new enemy offscreen
int spawn_enemy() {
    // Go trough the array searching for an inactive enemy slot
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            // Randomly choose which side of the screen to spawn from
            int side = rand() % 4;  // 0: top, 1: right, 2: bottom, 3: left
            
            double pos_x, pos_y;
            const int SPAWN_OFFSET = 10;  // Distance from arena edge
            
            // Position the enemy offscreen based on the chosen side
            switch (side) {
                case 0: // Top
                    // 2528 -> Arena width | 54 -> Enemy width
                    pos_x = rand() % (2528 - 54);  // Ensure enemy fits within arena width
                    pos_y = -SPAWN_OFFSET;
                    break;
                case 1: // Right
                    // 2528 -> Arena width | 87 -> Enemy height
                    pos_x = 2528 + SPAWN_OFFSET;
                    pos_y = rand() % (2528 - 87);  // Ensure enemy fits within arena height
                    break;
                case 2: // Bottom
                    // 2528 -> Arena width | 54 -> Enemy width
                    pos_x = rand() % (2528 - 54);  // Ensure enemy fits within arena width
                    pos_y = 2528 + SPAWN_OFFSET;
                    break;
                case 3: // Left
                    // 2528 -> Arena width | 87 -> Enemy height
                    pos_x = -SPAWN_OFFSET;
                    pos_y = rand() % (2528 - 87);  // Ensure enemy fits within arena height
                    break;
            }
            
            // Create the enemy entity with its animations
            enemies[i].base = create_entity_full(pos_x, pos_y, 0, 0, 100, 8, enemy_animations);
            if (enemies[i].base == NULL) return 1;
            
            enemies[i].active = true;
            return 0;
        }
    }
    return 1;  // No available slots
}

// Check if an enemy collides with the player
static bool check_collision(entity* enemy, entity* player) {
    // Simple box collision detection | Using correct sprite dimensions
    const double ENEMY_WIDTH = 54;
    const double ENEMY_HEIGHT = 87;
    const double PLAYER_WIDTH = 72;
    const double PLAYER_HEIGHT = 96;

    // Check if the boxes overlap, needs to be improved
    return (enemy->pos_x < player->pos_x + PLAYER_WIDTH &&
            enemy->pos_x + ENEMY_WIDTH > player->pos_x &&
            enemy->pos_y < player->pos_y + PLAYER_HEIGHT &&
            enemy->pos_y + ENEMY_HEIGHT > player->pos_y);
}

// Update all active enemies, move them towards the player and check for collisions
bool update_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && enemies[i].base != NULL) {
            entity* enemy = enemies[i].base;
            entity* player = active_arena->player;

            // Calculate direction to player
            double dx = player->pos_x - enemy->pos_x;
            double dy = player->pos_y - enemy->pos_y;
            
            // Get the distance between the enemy and the player
            double length = sqrt(dx * dx + dy * dy); 
            if (length > 0) {
                dx /= length;
                dy /= length;
            }

            // Set enemy speed towards player
            const double ENEMY_SPEED = 2;
            enemy->speed_x = dx * ENEMY_SPEED;
            enemy->speed_y = dy * ENEMY_SPEED;

            // Move the enemy
            move_entity(enemy);

            // Check for collision with player
            if (check_collision(enemy, player)) {
                return true;  // Collision detected
            }
        }
    }
    return false;  // No collision
}

// Draw all active enemies
void draw_enemies(arena* arena) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && enemies[i].base != NULL) {
            // Get the current animation based on the enemy's direction
            animation animation = enemies[i].base->animations[get_entity_direction(enemies[i].base)];
            
            // Draw the enemy relative to the arena's position
            vg_draw_image32(
                enemies[i].base->pos_x - arena->pos_x,
                enemies[i].base->pos_y - arena->pos_y,
                animation.sprites[(get_current_frame() % (animation.n_frames * 8)) / 8]
            );
        }
    }
}

// Clean up enemy resources
void cleanup_enemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && enemies[i].base != NULL) {
            destroy_entity(enemies[i].base);
            enemies[i].base = NULL;
        }
        enemies[i].active = false;
    }
}
