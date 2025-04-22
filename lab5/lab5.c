// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphics.h"
#include "keyboard.h"

// Any header files included below this line should have been created by you

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

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if(set_VBE_mode(mode)) return 1;

  // lazy option
  tickdelay(micros_to_ticks(delay * 1000000));

  if(vg_exit()) return 1;

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  int ipc_status, r;
  uint8_t keyboard_bit_no = 0;
  message msg;
 
  if(keyboard_subscribe_int_exclusive(&keyboard_bit_no)) return 1;
  if(graphics_init(mode)) return 1;

  if(vg_draw_rectangle(x, y, width, height, color))
    printf("failed to draw rectangle");

  while(get_scancode() != ESC_KEY_BREAKCODE) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:		
          if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
            if(!valid_kbc_output(false)){ // check if the output buffer has valid data
              discard_kbc_output(); // discard if not
            }
            else kbc_ih(); // handle interrupt if yes
          }
          break;
      }
    }
  }

  if(keyboard_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
    int ipc_status, r;
    uint8_t keyboard_bit_no = 0;
    message msg;
    vbe_mode_info_t mode_info;


    // Subscribe keyboard
    if(keyboard_subscribe_int_exclusive(&keyboard_bit_no)) return 1;

    // Initialize graphics
    if(graphics_init(mode)) return 1;

    // Get mode information
    mode_info = get_current_mode_info();


    // Calculate rectangle dimensions
    uint16_t rect_width = mode_info.XResolution / no_rectangles;
    uint16_t rect_height = mode_info.YResolution / no_rectangles;

    for (uint8_t row = 0; row < no_rectangles; row++) {
      for (uint8_t col = 0; col < no_rectangles; col++) {
        uint32_t color;
        
        if (is_direct_color_model()) {
          // Direct color mode
          uint32_t R = 
            (get_red_color_field(first) + col * step) % (1 << mode_info.RedMaskSize);
          uint32_t G = 
            (get_green_color_field(first) + row * step) % (1 << mode_info.GreenMaskSize);
          uint32_t B = 
            (get_blue_color_field(first) + (col + row) * step) % (1 << mode_info.BlueMaskSize);

          color = (R << mode_info.RedFieldPosition) | 
                  (G << mode_info.GreenFieldPosition) | 
                  (B << mode_info.BlueFieldPosition);
        } else {
          // Indexed color mode
          color = (first + (row * no_rectangles + col) * step) % (1 << get_bits_per_pixel());
        }

        if(vg_draw_rectangle(col * rect_width, row * rect_height, 
                            rect_width, rect_height, color)) {
          printf("Failed to draw rectangle at (%d,%d)\n", row, col);
        }
      }
    }

    // Wait for ESC key to finalize
    while(get_scancode() != ESC_KEY_BREAKCODE) {
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE:		
            if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
              if(!valid_kbc_output(false)){ // check if the output buffer has valid data
                discard_kbc_output(); // discard if not
              }
              else kbc_ih(); // handle interrupt if yes
            }
            break;
        }
      }
    }

    // Cleanup before termination
    if(keyboard_unsubscribe_int()) return 1;
    if(vg_exit()) return 1;

    return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
