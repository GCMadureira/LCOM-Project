#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>
#include "vbe.h"

int (set_VBE_mode)(uint16_t mode);

int (graphics_init)(uint16_t mode);

void* (get_video_mem)();
unsigned int (get_hres)();
unsigned int (get_vres)();
unsigned int (get_bits_per_pixel)();

int (map_video_memory)(uint16_t mode);

#endif /*_GRAPHICS_H */
