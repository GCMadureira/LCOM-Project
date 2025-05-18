#include "animations.h"

animation* pharaoh_animations;


int (load_animations)() {
  //for now, only the pharaoh animations
  load_pharaoh_animations();
  return 0;
}

enum animation_direction (get_entity_direction)(entity* entity) {
  if(entity->speed_x > 0 && entity->speed_y > 0) return DOWN_RIGHT;
  if(entity->speed_x > 0 && entity->speed_y < 0) return UP_RIGHT;
  if(entity->speed_x > 0 && entity->speed_y == 0) return RIGHT;
  if(entity->speed_x < 0 && entity->speed_y > 0) return DOWN_LEFT;
  if(entity->speed_x < 0 && entity->speed_y < 0) return UP_LEFT;
  if(entity->speed_x < 0 && entity->speed_y == 0) return LEFT;
  if(entity->speed_x == 0 && entity->speed_y > 0) return DOWN;
  if(entity->speed_x == 0 && entity->speed_y < 0) return UP;
  return entity->idle_front ? IDLE_FRONT : IDLE_BACK;
}


int (clean_animations)() {
  destroy_animation(pharaoh_animations[0]);
  destroy_animation(pharaoh_animations[1]);

  free(pharaoh_animations);

  return 0;
}

int (destroy_animation)(animation animation) {
  for(uint32_t i = 0; i < animation.n_frames; ++i){
    free(animation.sprites[i]);
  }
  free(animation.sprites);

  return 0;
}

static int (load_pharaoh_animations)() {
  #include "../resources/Pharaoh Idle Back/pharaoh_idle_back.h"
  #include "../resources/Pharaoh Idle Front/pharaoh_idle_front.h"
  //#include "../resources/Pharaoh Walk Left/pharaoh_walk_left.h"

  xpm_image_t** sprites;
  xpm_image_t* current_image;

  pharaoh_animations = (animation*)malloc(sizeof(animation) * 10); //one for each direction

  //pharaoh idle back
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 2);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_back_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_back_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;

  pharaoh_animations[UP] = (animation){2, sprites};
  pharaoh_animations[UP_RIGHT] = (animation){2, sprites};
  pharaoh_animations[UP_LEFT] = (animation){2, sprites};
  pharaoh_animations[IDLE_BACK] = (animation){2, sprites};
  

  //pharaoh idle front
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 4);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_front_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_front_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_front_2, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[2] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_front_3, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[3] = current_image;

  pharaoh_animations[DOWN] = (animation){4, sprites};
  pharaoh_animations[DOWN_RIGHT] = (animation){4, sprites};
  pharaoh_animations[DOWN_LEFT] = (animation){4, sprites};
  pharaoh_animations[IDLE_FRONT] = (animation){4, sprites};
  pharaoh_animations[LEFT] = (animation){4, sprites};
  pharaoh_animations[RIGHT] = (animation){4, sprites};

  
  return 0;
}
