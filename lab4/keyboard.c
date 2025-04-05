#include "keyboard.h"


int kbd_hook_id;
uint8_t scancode = 0;
uint32_t sys_inb_calls = 0;

u_int8_t (get_scancode)(){
  return scancode;
}

uint32_t (get_sys_inb_calls)(){
  return sys_inb_calls;
}

int (keyboard_subscribe_int_exclusive)(uint8_t *bit_no){
  kbd_hook_id = *bit_no;
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id);
}

int (keyboard_unsubscribe_int)(){
  return sys_irqrmpolicy(&kbd_hook_id);
}

bool (is_breakcode)(uint8_t scancode){
  return (scancode & BREAKCODE);
}

void (kbc_ih)() {
  uint8_t status;
  util_sys_inb(KBC_OUT_REG, &status);
  scancode = status;
}

int (keyboard_reenable_interrupts)(){
  uint8_t status;
  for(int i = 0; i < 5; ++i){ //wait for 100ms max
    if(util_sys_inb(KBC_STAT_REG, &status)) continue;
    if((status & KBC_ST_IBF) == 0){ //if input buffer is empty
      read_kbc_command(&status); //read old command byte
      write_kbc_command_arg(WR_CMD_BYTE, status | KBD_ENABLE_INT); //enable interrupts again
      return 0;
    }
    tickdelay(micros_to_ticks(20000));
  }
  return 1;
}
