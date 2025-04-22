#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>
#include "vbe.h"

int (set_VBE_mode)(uint16_t mode);

int (graphics_init)(uint16_t mode);

void* (get_video_mem)();
vbe_mode_info_t (get_current_mode_info)();
unsigned int (get_hres)();
unsigned int (get_vres)();
unsigned int (get_bits_per_pixel)();
bool (is_direct_color_model)();

uint32_t (get_red_color_field)(const uint32_t color);
uint32_t (get_green_color_field)(const uint32_t color);
uint32_t (get_blue_color_field)(const uint32_t color);

int (map_video_memory)(uint16_t mode);

#endif /*_GRAPHICS_H */
