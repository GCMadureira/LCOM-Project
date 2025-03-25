#include <lcom/lcf.h>

#include "keyboard.h"


int hook_id;
uint8_t scancode;
uint32_t sys_inb_calls = 0;

int (keyboard_subscribe_int_exclusive)(uint8_t *bit_no){
  hook_id = *bit_no;
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (keyboard_unsubscribe_int)(){
  return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)() {
  uint8_t status;

  #ifdef LAB3
  sys_inb_calls++;
  #endif

  if(util_sys_inb(KBC_STAT_REG, &status)) return; //error reading status register
  if(status & (KBC_PAR_ERR | KBC_TO_ERR)) return; //parity error or timeout error
  if(status & KBC_OBF){

    #ifdef LAB3
    sys_inb_calls++;
    #endif

    util_sys_inb(KBC_OUT_REG, &status);
    scancode = status;
  }
}
