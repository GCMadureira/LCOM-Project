#include "mouse.h"

int mouse_hook_id;

int (mouse_subscribe_int_exclusive)(uint8_t *bit_no){
  mouse_hook_id = *bit_no;
  return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_int)(){
  return sys_irqrmpolicy(&mouse_hook_id);
}