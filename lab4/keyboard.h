#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <lcom/utils.h>
#include <lcom/timer.h>
#include "i8042.h"

int (keyboard_subscribe_int_exclusive)(uint8_t *bit_no);
int (keyboard_unsubscribe_int)();
bool (is_breakcode)(uint8_t scancode);

u_int8_t (get_scancode)();
uint32_t (get_sys_inb_calls)();

int (write_kbc_command)(uint8_t command);
int (write_kbc_command_arg)(uint8_t command, uint8_t arg);
int (read_kbc_command)(uint8_t* command);
int (keyboard_reenable_interrupts)();


#endif /* _LCOM_I8042_H_ */
