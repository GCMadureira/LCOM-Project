#include "graphics.h"
#include <math.h>


static char* video_mem = NULL;
static vbe_mode_info_t mode_info;

void* (get_video_mem)(){
  return video_mem;
}

vbe_mode_info_t (get_current_mode_info)(){
  return mode_info;
}

unsigned int (get_hres)(){
  return mode_info.XResolution;
}

unsigned int (get_vres)(){
  return mode_info.YResolution;
}

unsigned int (get_bits_per_pixel)(){
  return mode_info.BitsPerPixel;
}

bool (is_direct_color_model)(){
  return mode_info.MemoryModel == DIRECT_COLOR;
}

uint32_t (get_red_color_field)(const uint32_t color){
  return (color >> mode_info.RedFieldPosition) & ((1 << mode_info.RedMaskSize) - 1);
}

uint32_t (get_green_color_field)(const uint32_t color){
  return (color >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize) - 1);
}

uint32_t (get_blue_color_field)(const uint32_t color){
  return (color >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize) - 1);
}

int (graphics_init)(uint16_t mode){
  if(map_video_memory(mode)) return 1;
  return set_VBE_mode(mode);
}

int (set_VBE_mode)(uint16_t mode){
  reg86_t r86;
  memset(&r86, 0, sizeof(r86));

  r86.intno = VIDEO_INT_INSTRUCTION;
  r86.ah = VBE_FUNCTION;
  r86.al = VBE_SET_MODE;
  r86.bx = LINEAR_FRAME_BUFFER | mode;
  
  if(sys_int86(&r86) != OK) return 1;
  if(r86.al != VBE_FUNCTION_SUPPORTED) return 1; // function not supported
  if(r86.ah) return 1; // function not successful

  return 0;
}


int (map_video_memory)(uint16_t mode){
  struct minix_mem_range mr;
  unsigned int vram_base;
  unsigned int vram_size;
  
  int r;    

  /* Use VBE function 0x01 to initialize vram_base and vram_size */

  // get the mode information
  if(vbe_get_mode_info(mode, &mode_info)) return 1;

  vram_base = mode_info.PhysBasePtr;
  vram_size = get_hres()*get_vres()*ceil((double)get_bits_per_pixel()/8);

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if(OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return 1;
  }

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED) {
    panic("couldn't map video memory");
    return 1;
  }

  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  if(video_mem == NULL) return 1;
  if(x < 0 || x >= get_hres() || y < 0 || y >= get_vres()) return 1;

  // ceil accounts for bits per pixel like mode 0x110 (not multiple of 8)
  int bytes_per_pixel = ceil((double)get_bits_per_pixel()/8);

  unsigned offset = (y * get_hres() + x) * bytes_per_pixel;
  for(unsigned int i = x; i < x + len && i < get_hres(); ++i){
    memcpy(video_mem + offset, &color, bytes_per_pixel);
    offset += bytes_per_pixel;
  }

  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  if(video_mem == NULL) return 1;
  if(x < 0 || x >= get_hres() || y < 0 || y >= get_vres()) return 1;

  for(int i = y; i < y + height; ++i){
    vg_draw_hline(x, i, width, color);
  }

  return 0;
}
