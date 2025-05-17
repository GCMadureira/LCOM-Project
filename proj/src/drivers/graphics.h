#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>
#include "vbe.h"
#include "../macros/colors.h"

int (set_VBE_mode)(uint16_t mode);
int (graphics_init)(uint16_t mode);
int (map_video_memory)(uint16_t mode);

void* (get_video_mem)();
vbe_mode_info_t (get_current_mode_info)();
unsigned int (get_hres)();
unsigned int (get_vres)();
unsigned int (get_bits_per_pixel)();
bool (is_direct_color_model)();

uint32_t (get_red_color_field)(const uint32_t color);
uint32_t (get_green_color_field)(const uint32_t color);
uint32_t (get_blue_color_field)(const uint32_t color);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_rectangle32)(int32_t x, int32_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_image32)(int32_t x, int32_t y, xpm_image_t* img_info);
int (vg_draw_image_section32)(int32_t x, int32_t y, xpm_image_t* img_info, uint16_t x_section,  uint16_t y_section, uint16_t width, uint16_t height);

int (show_frame)();

#endif /*_GRAPHICS_H */
