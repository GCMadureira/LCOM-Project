#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <lcom/lcf.h>
#include <lcom/utils.h>
#include <lcom/timer.h>

#include "i8042.h"
#include "kbc.h"

int (keyboard_subscribe_int_exclusive)(uint8_t *bit_no);
int (keyboard_unsubscribe_int)();
bool (keyboard_is_breakcode)(uint8_t scancode);

u_int8_t (keyboard_get_scancode)();

int (keyboard_reenable_interrupts)();


#endif /* _KEYBOARD_H_ */
