// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "kbc.h"
#include "mouse.h"

extern int counter;

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
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
