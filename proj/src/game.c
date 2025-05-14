#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "drivers/drivers.h"
#include "macros/colors.h"
#include "macros/scancodes.h"
#include "events/events.h"
#include "resources/xpm_files.h"
#include "model/sprites.h"


int (game_init)() {
  uint8_t timer_int_no = 0, keyboard_int_no = 1, mouse_int_no = 2;
  const int frame_rate = 60;

  if(timer_set_frequency(TIMER_0, frame_rate)) return 1; // set the frame rate on timer 0
  if(timer_subscribe_int(&timer_int_no)) return 1; // subscribe the timer 0 interruptions
  if(keyboard_subscribe_int_exclusive(&keyboard_int_no)) return 1; // subscribe keyboard ints
  if(mouse_stream_enable_data_reporting()) return 1; // enable reporting on the mouse
  if(mouse_subscribe_int_exclusive(&mouse_int_no)) return 1; // subscribe the interruptions reported
  if(graphics_init(0x14C)) return 1; // set the graphics mode as 0x14C and map the vmem
  if(loadAllXpm()) return 1; // at the end load all the xpm image assets

  return 0;
}

int (game_clean)() {
  return timer_unsubscribe_int() |
  keyboard_unsubscribe_int() |
  mouse_unsubscribe_int() |
  mouse_stream_disable_data_reporting() |
  vg_exit() | clear_events() |
  timer_set_frequency(TIMER_0, 60);
}

int (proj_main_loop)() {
  if(game_init()) {
    printf("Error: could not initialize the game\n");
    if(game_clean()) printf("Warning: something went wrong while cleaning up\n");
    return 1;
  }

  int ipc_status, r;
  message msg;

  unsigned long frame = 0;

  entity* player = create_entity(1, (xpm_image_t*[]){&sprite_img});
  vg_draw_image32(0, 0, &background_img);
  draw_entity(player);

  // main loop
  while(get_scancode() != ESC_KEY_BREAKCODE) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:		
          if (msg.m_notify.interrupts & BIT(0)) { // timer, execute one frame
            ++frame;

            vg_draw_image_section32(0, 0, &background_img, player->position.x, player->position.y, sprite_img.width, sprite_img.height);

            input_event event;
            while(get_next_event(&event) == 0) {  
              if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_MK_W) 
                player->speed.y = -2;
              else if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_MK_S) 
                player->speed.y = 2;
              else if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_MK_D) 
                player->speed.x = 2;
              else if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_MK_A) 
                player->speed.x = -2;
              else if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_BK_W) 
                player->speed.y = 0;
              else if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_BK_S) 
                player->speed.y = 0;
              else if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_BK_D) 
                player->speed.x = 0;
              else if(event.event_type == KEYBOARD_EVENT && event.scancode_byte1 == KEY_BK_A) 
                player->speed.x = 0;
            }

            move_entity(player);
            draw_entity(player);
          }
          if (msg.m_notify.interrupts & BIT(1)) { // keyboard
            handle_keyboard_event();
          }
          if (msg.m_notify.interrupts & BIT(2)) { // mouse
            handle_mouse_event();
          }
          break;
      }
    }
  }

  if(game_clean()) {
    printf("Warning: something went wrong while cleaning up\n");
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  //lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}
