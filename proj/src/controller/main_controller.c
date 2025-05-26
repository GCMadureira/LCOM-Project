#include "main_controller.h"

static menu* active_menu = NULL;
static arena* active_arena = NULL;

static enum game_state game_state = MAIN_MENU;
static unsigned long frame = 0;

const double COS45 = 0.70710678118;

enum game_state (get_game_state)(){
  return game_state;
}

unsigned long (get_current_frame)() {
  return frame;
}

static int (process_menu)(){
  input_event event;
  while(events_get_next(&event) == 0) {
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
            active_arena = arena_create();
            menu_destroy(active_menu);
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

  while(events_get_next(&event) == 0) {
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
  
  return 0;
}

int (process_frame)() {
  // the game state can change on the process part, need to separate it
  if(game_state == MAIN_MENU) process_menu();
  else if(game_state == GAME) process_game();

  if(game_state == MAIN_MENU) draw_menu(active_menu);
  else if(game_state == GAME) {
    if(arena_process_frame(active_arena) == 1) {
      // Return to main menu
      game_state = MAIN_MENU;
      active_menu = menu_create_main();
      arena_destroy(active_arena);
      active_arena = NULL;
    }
    else draw_arena(active_arena);
  }

  vg_show_frame();
  ++frame;

  return 0;
}

int (setup_game)() {
  if(static_images_load()) return 1;
  if(animations_load()) return 1;
  active_menu = menu_create_main();
  game_state = MAIN_MENU;
  return 0;
}

int (clean_game)() {
  events_clear();
  animations_clean();
  if(active_menu != NULL) menu_destroy(active_menu);
  if(active_arena != NULL) arena_destroy(active_arena);
  return 0;
}

