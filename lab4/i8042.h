#ifndef _I8042_H_
#define _I8042_H_

#include <lcom/lcf.h>

#define KEYBOARD_IRQ 1 // keyboard IRQ line
#define MOUSE_IRQ 12 // mouse IRQ line

// KBC registers
#define KBC_STAT_REG 0x64 // KBC status register (for reading)
#define KBC_CMD_REG 0x64 // KBC command register (for writing)
#define KBC_OUT_REG 0x60 // KBC output register (for reading)
#define KBC_CMDARG_REG 0x60 // KBC command argument register (for writing)

// KBC status byte
#define KBC_PAR_ERR BIT(7) // KBC status byte parity error
#define KBC_TO_ERR BIT(6) // KBC status byte timeout error
#define KBC_ST_AUX BIT(5) // KBC status byte aux bit (1 if mouse data, 0 if keyboard data)
#define KBC_ST_IBF BIT(1) // KBC status byte input buffer full
#define KBC_ST_OBF BIT(0) // KBC status byte output buffer full

// KBC commands
#define RD_CMD_BYTE 0x20 // KBC command to read command byte
#define WR_CMD_BYTE 0x60 // KBC command to write command byte
#define WR_MOUSE_BYTE 0xD4 //  KBC command to write a byte directly to the mouse

// KBC command byte
#define KBD_ENABLE_INT BIT(1) // KBC command byte, bit to enable keyboard interrupts
#define MOUSE_ENABLE_INT BIT(2) // KBC command byte, bit to enable mouse interrupts

// Keyboard scancodes
#define ESC_KEY_BREAKCODE 0x81 // ESC key scancode's breakcode
#define EXTENDED_SCANCODE 0xE0 // First of two bytes scancode
#define BREAKCODE BIT(7) // Breakcode bit

// Mouse byte commands
#define DISABLE_DATA_REPORTING 0xF5 // mouse command to disable data reporting in stream mode
#define ENABLE_DATA_REPORTING 0xF4 // mouse command to enable data reporting in stream mode
#define MOUSE_BYTE_ACK 0xFA // acknowledgement value if the mouse byte sent is valid
#define MOUSE_BYTE_NACK 0xFE // acknowledgement value if the mouse byte sent is invalid, resend
#define MOUSE_BYTE_ERROR 0xFC // acknowledgement value if the mouse byte sent generated and error

// Mouse data packet
#define LEFT_BUTTON_PRESSED BIT(0)
#define RIGHT_BUTTON_PRESSED BIT(1)
#define MIDDLE_BUTTON_PRESSD BIT(2)
#define MSB_X_DELTA BIT(4)
#define MSB_Y_DELTA BIT(5)
#define X_OVERFLOW BIT(6)
#define Y_OVERFLOW BIT(7)


#endif /*_I8042_H */
