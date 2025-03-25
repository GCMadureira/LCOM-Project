#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

// macros
#define KEYBOARD_IRQ 1

#define KBC_STAT_REG 0x64
#define KBC_OUT_REG 0x60

#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)
#define KBC_OBF BIT(0)

// functions
int (keyboard_subscribe_int_exclusive)(uint8_t *bit_no);
int (keyboard_unsubscribe_int)();

u_int8_t (get_scancode)();
uint32_t (get_sys_inb_calls)();

#endif /* _LCOM_I8042_H_ */
