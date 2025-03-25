#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <lcom/utils.h>
#include <lcom/timer.h>


// macros
#define KEYBOARD_IRQ 1

#define KBC_STAT_REG 0x64
#define KBC_CMD_REG 0x64
#define KBC_OUT_REG 0x60
#define KBC_CMDARG_REG 0x60

#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)
#define KBC_ST_IBF BIT(1)
#define KBC_ST_OBF BIT(0)

#define RD_CMD_BYTE 0x20
#define WR_CMD_BYTE 0x60

#define ESC_KEY_BREAKCODE 0x81


// functions
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
