#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "drivers/drivers.h"
#include "resources/xpm_files.h"


int (game_init)() {
  uint8_t timer_int_no = 0, keyboard_int_no = 1, mouse_int_no = 2;
  const int frame_rate = 60;
  if(timer_set_frequency(TIMER_0, frame_rate)) return 1;
  if(timer_subscribe_int(&timer_int_no)) return 1;
  if(keyboard_subscribe_int_exclusive(&keyboard_int_no)) {
    timer_unsubscribe_int();
    return 1;
  }
  if(mouse_stream_enable_data_reporting()) {
    timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    return 1;
  }
  if(mouse_subscribe_int_exclusive(&mouse_int_no)) {
    timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    mouse_stream_disable_data_reporting();
    return 1;
  }
  if(graphics_init(0x14C)) {
    timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    mouse_stream_disable_data_reporting();
    mouse_unsubscribe_int();
    vg_exit();
    return 1;
  }
  return 0;
}

int (game_clean)() {
  return timer_unsubscribe_int() |
  keyboard_unsubscribe_int() |
  mouse_unsubscribe_int() |
  mouse_stream_disable_data_reporting() |
  vg_exit();
}

int (proj_main_loop)() {
  if(game_init()) {
    printf("Error: could not initialize the game\n");
    return 1;
  }

  int ipc_status, r;
  message msg;

  unsigned long frame = 0;

  xpm_image_t img_info;
  uint8_t* img = xpm_load(background_quit_xpm, XPM_8_8_8_8, &img_info);
  if(img == NULL) {
    if(game_clean()) {
      printf("Warning: something went wrong while cleaning up\n");
      return 1;
    }
  }

  vg_draw_image32(100,100,img_info);

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

          }
          if (msg.m_notify.interrupts & BIT(1)) { // keyboard
            if(!valid_kbc_output(false)){ // check if the output buffer has valid data
              discard_kbc_output(); // discard if not
            }
            else kbc_ih(); // handle interrupt if yes
          }
          if (msg.m_notify.interrupts & BIT(2)) { // mouse
            if(!valid_kbc_output(true)){ // check if the output buffer has valid data
              discard_kbc_output(); // discard if not
            }
            else mouse_ih(); // handle interrupt if yes
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
