// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphics.h"
#include "keyboard.h"

extern int counter;

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
  int ipc_status, r;
  uint8_t keyboard_bit_no = 0;
  message msg;
  //vbe_mode_info_t mode_info;

  if(keyboard_subscribe_int_exclusive(&keyboard_bit_no)) return 1;
  if(graphics_init(0x105)) return 1;

  xpm_image_t img_info;
  uint8_t* img = xpm_load(xpm, XPM_INDEXED, &img_info);
  if(img == NULL) return 1;

  //uint16_t size = 10; // draw the image bigger

  for(int y_off = 0; y_off < img_info.height; ++y_off){
    for(int x_off = 0; x_off < img_info.width; ++x_off){
      vg_draw_pixel(x + x_off, y + y_off, *(img + y_off * img_info.width + x_off));
      //vg_draw_rectangle(x + x_off*size, y + y_off*size, size, size, *(img + y_off * img_info.width + x_off));
    }
  }

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

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
  int16_t speed, uint8_t fr_rate) {

  int ipc_status, r;
  message msg;
  uint8_t timer_bit_no = 0, keyboard_bit_no = 1;

  // Load XPM image
  xpm_image_t img_info;
  uint8_t* img = xpm_load(xpm, XPM_INDEXED, &img_info);
  if(img == NULL) return 1;

  // Calculate movement parameters
  int16_t dx = xf - xi;  // horizontal movement
  int16_t dy = yf - yi;  // vertical movement

  // Ensure only horizontal or vertical movement
  if(dx != 0 && dy != 0) {
    return 1;
  }

  // Subscribe to interrupts
  if(timer_subscribe_int(&timer_bit_no)) return 1;
  if(keyboard_subscribe_int_exclusive(&keyboard_bit_no)) return 1;

  if(timer_set_frequency(0, fr_rate)) {
    timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    return 1;
  }

  // Initialize graphics mode 0x105
  if(graphics_init(0x105)) return 1;


  // Calculate total distance and frames needed
  int16_t total_distance = (dx != 0) ? abs(dx) : abs(dy);
  int16_t frames_needed;
  int16_t x_speed = 0, y_speed = 0;

  if(speed > 0) {
    // Speed is pixels per frame
    x_speed = speed;
    frames_needed = total_distance/speed + 1 + (total_distance%speed != 0);
    // frames with movement + 1 initial frame + 1 frame for the remaining distance left < speed
  } else {
  // Speed is frames per pixel
    x_speed = 1;
    frames_needed = (total_distance + 1) * (-speed);
  }

  if(dx < 0 || dy < 0) x_speed *= -1; // if movement is to the left
  if(dy != 0) { // if movement is on the y axis instead of the x axis, invert speeds
    y_speed = x_speed;
    x_speed = 0;
  }

  // Current position
  uint16_t current_x = xi;
  uint16_t current_y = yi;
  int frame = 0;

  while(get_scancode() != ESC_KEY_BREAKCODE && frame < frames_needed) {
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
          if (msg.m_notify.interrupts & BIT(timer_bit_no)) {
            timer_int_handler();

            if(counter % (speed < 0 ? abs(speed) : 1) == 0) { // account for negative speed
              ++frame;

              // Clear previous position by drawing a black rectangle
              vg_draw_rectangle(current_x - x_speed, current_y - y_speed, img_info.width, img_info.height, 0);

              // Draw sprite at new position
              for(int y_off = 0; y_off < img_info.height; ++y_off) {
                for(int x_off = 0; x_off < img_info.width; ++x_off) {
                  vg_draw_pixel(current_x + x_off, current_y + y_off, 
                    *(img + y_off * img_info.width + x_off));
                }
              }

              // Horizontal movement
              current_x += x_speed;
              if((dx > 0 && current_x > xf) || (dx < 0 && current_x < xf)) 
                current_x = xf;

              // Vertical movement
              current_y += y_speed;
              if((dy > 0 && current_y > yf) || (dy < 0 && current_y < yf)) 
                current_y = yf;
            }
          }
          break;
      }
    }
  }

  // Cleanup
  if(timer_unsubscribe_int()) return 1;
  if(keyboard_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}

