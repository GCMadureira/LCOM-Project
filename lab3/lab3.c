#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"

extern int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_status, r;
  uint8_t bit_no = 0;
  message msg;
  bool extended_flag = false;
 
  keyboard_subscribe_int_exclusive(&bit_no);

  while(get_scancode() != ESC_KEY_BREAKCODE) {
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */				
          if (msg.m_notify.interrupts & BIT(bit_no)) { /* subscribed interrupt */
            kbc_ih(); // handle interrupt

            if(get_scancode() == TWO_BYTES) //wait for next interrupt
              extended_flag = true;
            else if(extended_flag){ //received the second byte, therefore print
              kbd_print_scancode(!is_breakcode(get_scancode()), 2, ((uint8_t[]){TWO_BYTES, get_scancode()}));
              extended_flag = false;
            }
            else //one byte scancode, can print directly
              kbd_print_scancode(!is_breakcode(get_scancode()), 1, ((uint8_t[]){get_scancode()}));

          }
          break;
        default:
          break; /* no other notifications expected: do nothing */	
      }
    } else { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }

  keyboard_unsubscribe_int();
  kbd_print_no_sysinb(get_sys_inb_calls());

  return 0;
}

int(kbd_test_poll)() {
  uint8_t status = 0;
  int sys_inb_calls = 0;
  bool extended_flag = false;
  while(status != ESC_KEY_BREAKCODE){
    sys_inb_calls++;

    //error reading status register, output register empty or invalid data
    if(util_sys_inb(KBC_STAT_REG, &status) 
    || !(status & KBC_ST_OBF) 
    || status & (KBC_PAR_ERR | KBC_TO_ERR))
      continue;

    sys_inb_calls++;

    util_sys_inb(KBC_OUT_REG, &status);
    if(status == 0xE0) //wait for next scancode
      extended_flag = true;
    else if(extended_flag){ //received the second byte, therefore print
      kbd_print_scancode(!is_breakcode(status), 2, ((uint8_t[]){0xE0, status}));
      extended_flag = false;
    }
    else //one byte scancode, can print directly
      kbd_print_scancode(!is_breakcode(status), 1, ((uint8_t[]){status}));
  }

  kbd_print_no_sysinb(sys_inb_calls);
  if(keyboard_reenable_interrupts()) return 1;
  return 0;
}

int(kbd_test_timed_scan)(uint8_t idle) {
  int ipc_status, r;
  uint8_t timer_bit_no = 0, keyboard_bit_no = 1;
  message msg;
  bool extended_flag = false;
 
  if(timer_subscribe_int(&timer_bit_no)) return 1;
  if(keyboard_subscribe_int_exclusive(&keyboard_bit_no)) return 1;

  while(get_scancode() != ESC_KEY_BREAKCODE && counter < 60 * idle) {
    /* Get a request message. */
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */				
          if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) { /* subscribed interrupt */
            kbc_ih(); // handle interrupt

            if(get_scancode() == 0xE0) //wait for next interrupt
              extended_flag = true;
            else if(extended_flag){ //received the second byte, therefore print
              kbd_print_scancode(!is_breakcode(get_scancode()), 2, ((uint8_t[]){0xE0, get_scancode()}));
              extended_flag = false;
            }
            else //one byte scancode, can print directly
              kbd_print_scancode(!is_breakcode(get_scancode()), 1, ((uint8_t[]){get_scancode()}));
            
            counter = 0;
          }
          if (msg.m_notify.interrupts & BIT(timer_bit_no)) {
            timer_int_handler();
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */	
      }
    } else { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }

  if(timer_unsubscribe_int()) return 1;
  if(keyboard_unsubscribe_int()) return 1;
  return 0;
}
