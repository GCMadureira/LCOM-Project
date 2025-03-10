#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = (uint8_t)val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = (uint8_t)(val >> 8);
  return 0;
}

int util_sys_inb(int port, uint8_t *value) {
    uint32_t temp_value; // Temporary variable to hold 32 bit variable

    // Call sys_inb to read the 32 bit
    if (sys_inb(port, &temp_value) != 0) {
        return 1; // If sys_inb != 0 it means an error occurred so return 1
    }

    // Copy the LSB of the 32 bit variable to the desired 8 bit variable
    *value = (uint8_t)(temp_value & 0xFF);


    return 0;
}
