#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>
#include "vbe.h"
#include "../macros/colors.h"

int (vg_set_VBE_mode)(uint16_t mode);
int (vg_graphics_init)(uint16_t mode);
int (vg_map_video_memory)(uint16_t mode);

void* (vg_get_video_mem)();
vbe_mode_info_t (vg_get_current_mode_info)();
unsigned int (vg_get_hres)();
unsigned int (vg_get_vres)();
unsigned int (vg_get_bits_per_pixel)();
bool (vg_is_direct_color_model)();

uint32_t (vg_get_red_color_field)(const uint32_t color);
uint32_t (vg_get_green_color_field)(const uint32_t color);
uint32_t (vg_get_blue_color_field)(const uint32_t color);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_rectangle32)(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_image32)(int32_t x, int32_t y, xpm_image_t* img_info);
int (vg_draw_image_section32)(int32_t x, int32_t y, xpm_image_t* img_info, uint16_t x_section,  uint16_t y_section, uint16_t width, uint16_t height);

int (vg_show_frame)();

#endif /*_GRAPHICS_H */
