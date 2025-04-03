#ifndef _I8042_H_
#define _I8042_H_

#include <lcom/lcf.h>

#define KEYBOARD_IRQ 1 // keyboard IRQ line

// KBC registers
#define KBC_STAT_REG 0x64 // KBC status register (for reading)
#define KBC_CMD_REG 0x64 // KBC command register (for writing)
#define KBC_OUT_REG 0x60 // KBC output register (for reading)
#define KBC_CMDARG_REG 0x60 // KBC command argument register (for writing)

// KBC status byte
#define KBC_PAR_ERR BIT(7) // KBC status byte parity error
#define KBC_TO_ERR BIT(6) // KBC status byte timeout error
#define KBC_ST_IBF BIT(1) // KBC status byte input buffer full
#define KBC_ST_OBF BIT(0) // KBC status byte output buffer full

// KBC commands
#define RD_CMD_BYTE 0x20 // KBC command to read command byte
#define WR_CMD_BYTE 0x60 // KBC command to write command byte

// KBC command byte
#define KBD_ENABLE_INT BIT(1) // KBC command byte, bit to enable keyboard interrupts
#define MOUSE_ENABLE_INT BIT(2) // KBC command byte, bit to enable mouse interrupts

// KBC keyboard scancodes
#define ESC_KEY_BREAKCODE 0x81 // ESC key scancode's breakcode
#define EXTENDED_SCANCODE 0xE0 // First of two bytes scancode
#define BREAKCODE BIT(7) // Breakcode bit

#endif /*_I8042_H */
