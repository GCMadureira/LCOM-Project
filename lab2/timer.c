#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t status;
  if(timer_get_conf(timer, &status) != 0) return 1; //get config as not to change the first 4 bits
  status &= 0x0F;

  if(freq < 19) return 1; //prevent overflow
  uint16_t realFreq = TIMER_FREQ/freq;
  uint8_t LSB; util_get_LSB(realFreq, &LSB);
  uint8_t MSB; util_get_MSB(realFreq, &MSB);

  switch (timer){
    case 0:
    case TIMER_0:
      sys_outb(TIMER_CTRL, 0x30 | status); //0b0011xxxx
      sys_outb(TIMER_0, LSB);
      sys_outb(TIMER_0, MSB);
      break;
    case 1:
    case TIMER_1:
      sys_outb(TIMER_CTRL, 0x60 | status); //0b0111xxxx
      sys_outb(TIMER_1, LSB);
      sys_outb(TIMER_1, MSB);
      break;
    case 2:
    case TIMER_2:
      sys_outb(TIMER_CTRL, 0xB0 | status); //0b1011xxxx
      sys_outb(TIMER_2, LSB);
      sys_outb(TIMER_2, MSB);
      break;
    default: //invalid timer
      return 1;
  }
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  switch (timer){
    case 0:
    case TIMER_0:
      sys_outb(TIMER_CTRL, 0xC2); //0b11000010
      break;
    case 1:
    case TIMER_1:
      sys_outb(TIMER_CTRL, 0xC4); //0b11000100
      break;
    case 2:
    case TIMER_2:
      sys_outb(TIMER_CTRL, 0xC8); //0b11001000
      break;
    default: //invalid timer
      return 1;
  }
  return util_sys_inb(timer, st);
}


// Work in progress !
int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  
  union timer_status_field_val conf;


    // This will check which field of the status byte we want to get to then display on timer_print_config
    // On each case ___: , we rewrite our conf variable to hold whichever bit/bits we want 
    switch (field) {
        case tsf_all:
            // Display entire status byte
            conf.byte = st;
            break;

        case tsf_initial:
            // Display initialization mode | Located on bits 4-5 | 3 different modes
            conf.in_mode = (st >> 4) & 0x03;
            break;

        case tsf_mode:
            // Display the counting mode | Located on bits 1-3 | 
            conf.count_mode = (st >> 1) & 0x07;
            break;

        case tsf_base:
            // Display counting base | Located on bit 0 | Either "Binary" or "BCD"
            conf.bcd = st & 0x01;
            break;

        default:
            return 1; // Invalid, return error
    }

    // Call timer_print_config to display the configuration
    return timer_print_config(timer, field, conf);

  return 1;
}
