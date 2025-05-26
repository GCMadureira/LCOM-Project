#include "main_controller.h"

static menu* active_menu = NULL;
arena* active_arena = NULL;
enum game_state game_state = MAIN_MENU;
static unsigned long frame = 0;
static unsigned long last_enemy_spawn = 0;  // Track when we last spawned an enemy

enum game_state (get_game_state)(){
  return game_state;
}

unsigned long (get_current_frame)() {
  return frame;
}

static int (process_menu)(){
  input_event event;
  while(get_next_event(&event) == 0) {
    if(event.event_type == KEYBOARD_EVENT) {
      switch (event.scancode_byte1) {
        case KEY_MK_W:
          menu_select_option_up(active_menu);
          break;
        case KEY_MK_S:
          menu_select_option_down(active_menu);
          break;
        case KEY_MK_ENTER:
          if (active_menu->menu_status == 0) {
            game_state = GAME;
            active_arena = create_arena();
            destroy_menu(active_menu);
            return 0;
          }
          else if (active_menu->menu_status == 1) game_state = QUIT;
          break;
      }
    }
  }

  return 0;
}

static int (process_game)(){
  entity* player = active_arena->player;
  input_event event;

  while(get_next_event(&event) == 0) {
    if(event.event_type == KEYBOARD_EVENT) {
      switch (event.scancode_byte1) {
        case KEY_MK_W: //moving up
          player->idle_front = false;
          player->speed_y = -3;
          break;
        case KEY_MK_S: //moving down
          player->idle_front = true;
          player->speed_y = 3;
          break;
        case KEY_MK_D: //moving right
          player->speed_x = 3;
          break;
        case KEY_MK_A: //moving left
          player->speed_x = -3;
          break;
        case KEY_BK_W:
          if(player->speed_y < 0) player->speed_y = 0;
          break;
        case KEY_BK_S:
          if(player->speed_y > 0) player->speed_y = 0;
          break;
        case KEY_BK_D:
          if(player->speed_x > 0) player->speed_x = 0;
          break;
        case KEY_BK_A:
          if(player->speed_x < 0) player->speed_x = 0;
          break;
      }
    }
  }

  // If update_enemies() returns true, the player has collided with an enemy
  if (update_enemies()) {
    // Clean up all enemies
    cleanup_enemies();
    // Reinitialize enemy system for next game
    init_enemies();
    
    // Return to main menu
    game_state = MAIN_MENU;
    active_menu = create_main_menu();
    destroy_arena(active_arena);
    active_arena = NULL;
    return 0;
  }
  
  return 0;
}

int (process_frame)() {
  // the game state can change on the process part, need to separate it
  if(game_state == MAIN_MENU) process_menu();
  else if(game_state == GAME) {
    process_game();
    handle_enemy_spawning();  // Handle enemy spawning
  }

  if(game_state == MAIN_MENU) draw_menu(active_menu);
  else if(game_state == GAME) {
    move_entities(active_arena);
    draw_arena(active_arena);
    draw_enemies(active_arena);
  }

  show_frame();
  ++frame;

  return 0;
}

int (setup_game)() {
  if(load_static_images()) return 1;
  if(load_animations()) return 1;
  if(init_enemies()) return 1;  // Initialize enemy system
  active_menu = create_main_menu();
  game_state = MAIN_MENU;
  return 0;
}

int (clean_game)() {
  clear_events();
  clean_animations();
  cleanup_enemies();  // Clean up enemy system
  if(active_menu != NULL) destroy_menu(active_menu);
  if(active_arena != NULL) destroy_arena(active_arena);
  return 0;
}

// Handle enemy spawning with a cooldown
void (handle_enemy_spawning)() {
  // Spawn a new enemy every 120 frames (2 seconds at 60 FPS)
  if (frame - last_enemy_spawn >= 120) {
    if (spawn_enemy() == 0) {  // If spawn was successful
      last_enemy_spawn = frame;
    }
  }
}
