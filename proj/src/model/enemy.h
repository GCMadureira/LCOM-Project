#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <lcom/lcf.h>
#include "structs.h"
#include "entity.h"
#include "arena.h"
#include "../controller/main_controller.h"

// Maximum number of enemies that can exist at once
#define MAX_ENEMIES 50

// Enemy structure that extends the base entity
typedef struct {
    entity* base;  
    bool active;   // Whether the enemy slot is being used or not
} enemy;

// Initialize the enemy system
int init_enemies();

// Spawn a new enemy offscreen
int spawn_enemy();

// Update all active enemies
// Returns true if a collision with player occurred
bool update_enemies();

// Draw all active enemies
void draw_enemies(arena* arena);

// Clean up enemy (used after a game over)
void cleanup_enemies();

#endif /* _ENEMY_H_ */
