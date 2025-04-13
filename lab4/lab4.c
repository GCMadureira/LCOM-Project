// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "kbc.h"
#include "mouse.h"

extern int counter;

enum gesture_state {
  INITIAL = 0, // nothing was done
  FIRST_LINE, // left button was pressed
  DIRECTION_CHANGE, // first line was completed and left button released
  SECOND_LINE, // right button was pressed after first line was finished
  COMPLETE // gesture was done correctly
};

enum gesture_state machine_state = INITIAL;
long long current_posX = 0, current_posY = 0;

void (reset_state_machine)(){
  machine_state = INITIAL;
  current_posX = 0;
  current_posY = 0;
}

void (update_gesture_state)(const struct packet* packet, uint8_t x_len, uint8_t tolerance){
  current_posX += packet->delta_x;
  current_posY += packet->delta_y;

  switch (machine_state) {
    case  INITIAL:
      if(packet->lb){
        machine_state = FIRST_LINE;
        current_posX = 0;
        current_posY = 0;
      }
      break;
    case FIRST_LINE: {
      double slope = (double)current_posY/current_posX;
      // slope smaller than 1, if negative then check next if
      if(slope < 1 && slope >= 0) reset_state_machine();
      else if((packet->delta_x < 0 && abs(packet->delta_x) > tolerance) ||
      (packet->delta_y < 0 && abs(packet->delta_y) > tolerance)) // wrong direction above tolerance
        reset_state_machine();
      else if(!packet->lb) {
        if(current_posX < x_len) reset_state_machine();
        else {
          machine_state = DIRECTION_CHANGE;
          current_posX = 0;
          current_posY = 0;
        }
      }
      break;
    }
    case DIRECTION_CHANGE:
      if(abs(packet->delta_x) > tolerance || abs(packet->delta_y) > tolerance)
        reset_state_machine();
      else if(packet->lb || packet->mb) reset_state_machine();
      else if(packet->rb){
        machine_state = SECOND_LINE;
        current_posX = 0;
        current_posY = 0;
      }
      break;
    case SECOND_LINE: {
      double slope = (double)current_posY/current_posX;
      // slope bigger than -1, if positive then check next if
      if(slope > -1 && slope <= 0) reset_state_machine();
      else if((packet->delta_x < 0 && abs(packet->delta_x) > tolerance) ||
      (packet->delta_y > 0 && abs(packet->delta_y) > tolerance)) // wrong direction above tolerance
        reset_state_machine();
      else if(!packet->rb){
        if(current_posX < x_len) reset_state_machine();
        else machine_state = COMPLETE;
      } 
      break;
    }
    default:
      break;
  }
}


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  //lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  int ipc_status, r;
  uint8_t bit_no = 0;
  message msg;

  uint8_t packet_bytes[3];
  int state = 0; //0 means first byte, 1 means second by, 2 means third byte
 
  if(mouse_subscribe_int_exclusive(&bit_no)) return 1;
  if(mouse_stream_enable_data_reporting()) return 1;

  while(cnt > 0) {
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */				
          if (msg.m_notify.interrupts & BIT(bit_no)) { /* subscribed interrupt */
            if(!valid_kbc_output(true)){ //invalid output on kbc's output register
              discard_kbc_output();
              continue;
            }

            mouse_ih();
            uint8_t packet_byte = get_mouse_packet_byte();
            --cnt;

            // the first byte always has the bit 3 on, skip byte if it does not for synchronization
            if(state == 0 && !(packet_byte & BIT(3))) continue;
            packet_bytes[state] = packet_byte;
            if(state == 2){
              struct packet packet = assemble_packet(packet_bytes);
              mouse_print_packet(&packet);
            }
            state = (state + 1) % 3;
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */	
      }
    } else { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }

  if(mouse_unsubscribe_int()) return 1;
  if(mouse_stream_disable_data_reporting()) return 1;

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  int ipc_status, r;
  uint8_t mouse_bit_no = 1, timer_bit_no = 0;
  message msg;

  uint8_t packet_bytes[3];
  int state = 0; //0 means first byte, 1 means second by, 2 means third byte
 
  if(timer_subscribe_int(&timer_bit_no)) return 1;
  if(mouse_subscribe_int_exclusive(&mouse_bit_no)) return 1;
  if(mouse_stream_enable_data_reporting()) return 1;

  while(counter < idle_time * 60) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:		
          if (msg.m_notify.interrupts & BIT(mouse_bit_no)) {
            if(!valid_kbc_output(true)){ //invalid output on kbc's output register
              discard_kbc_output();
              continue;
            }

            mouse_ih();
            uint8_t packet_byte = get_mouse_packet_byte();

            // the first byte always has the bit 3 on, skip byte if it does not for synchronization
            if(state == 0 && !(packet_byte & BIT(3))) continue;
            packet_bytes[state] = packet_byte;
            if(state == 2){
              struct packet packet = assemble_packet(packet_bytes);
              mouse_print_packet(&packet);
            }
            state = (state + 1) % 3;

            counter = 0;
          }
          if(msg.m_notify.interrupts & BIT(timer_bit_no)){
            timer_int_handler();
          }
          break;
      }
    }
  }

  if(timer_unsubscribe_int()) return 1;
  if(mouse_unsubscribe_int()) return 1;
  if(mouse_stream_disable_data_reporting()) return 1;

  return 0;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
  int ipc_status, r;
  uint8_t bit_no = 0;
  message msg;

  uint8_t packet_bytes[3];
  int state = 0; //0 means first byte, 1 means second by, 2 means third byte
 
  if(mouse_subscribe_int_exclusive(&bit_no)) return 1;
  if(mouse_stream_enable_data_reporting()) return 1;

  while(machine_state != COMPLETE) {
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */				
          if (msg.m_notify.interrupts & BIT(bit_no)) { /* subscribed interrupt */
            if(!valid_kbc_output(true)){ //invalid output on kbc's output register
              discard_kbc_output();
              continue;
            }

            mouse_ih();
            uint8_t packet_byte = get_mouse_packet_byte();

            // the first byte always has the bit 3 on, skip byte if it does not for synchronization
            if(state == 0 && !(packet_byte & BIT(3))) continue;
            packet_bytes[state] = packet_byte;
            if(state == 2){
              struct packet packet = assemble_packet(packet_bytes);
              update_gesture_state(&packet, x_len, tolerance);
            }
            state = (state + 1) % 3;
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */	
      }
    } else { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }

  if(mouse_unsubscribe_int()) return 1;
  if(mouse_stream_disable_data_reporting()) return 1;

  return 0;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
