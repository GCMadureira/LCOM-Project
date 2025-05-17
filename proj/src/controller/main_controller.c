#include "main_controller.h"

static menu* active_menu;
static enum game_state game_state = MAIN_MENU;
static unsigned long frame = 0;

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
          if (active_menu->menu_status == 0) game_state = GAME;
          else if (active_menu->menu_status == 1) game_state = QUIT;
          break;
      }
    }
  }
  return 0;
}

static int (process_game)(){
  return 0;
}

int (process_frame)() {
  if(game_state == MAIN_MENU) {
    process_menu();
    draw_menu(active_menu);
  }
  else if(game_state == GAME) process_game();

  return 0;
}

int (setup_game)() {
  active_menu = create_main_menu();
  game_state = MAIN_MENU;
  return 0;
}

int (clean_game)() {
  destroy_menu(active_menu);
  return 0;
}
