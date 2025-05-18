#include "animations.h"

animation* pharaoh_animations;


enum animation_direction (get_entity_direction)(entity* entity) {
  if(entity->speed_x > 0 && entity->speed_y > 0) return DOWN_RIGHT;
  if(entity->speed_x > 0 && entity->speed_y < 0) return UP_RIGHT;
  if(entity->speed_x > 0 && entity->speed_y == 0) return RIGHT;
  if(entity->speed_x < 0 && entity->speed_y > 0) return DOWN_LEFT;
  if(entity->speed_x < 0 && entity->speed_y < 0) return UP_LEFT;
  if(entity->speed_x < 0 && entity->speed_y == 0) return LEFT;
  if(entity->speed_x == 0 && entity->speed_y > 0) return DOWN;
  if(entity->speed_x == 0 && entity->speed_y < 0) return UP;
  return entity->idle_front ? IDLE_DOWN : IDLE_UP;
}


int (clean_animations)() {
  for(int i = 0; i < 10; ++i)
    destroy_animation(pharaoh_animations[i]);

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
  #include "../resources/Pharaoh Idle Up/pharaoh_idle_up.h"
  #include "../resources/Pharaoh Idle Down/pharaoh_idle_down.h"
  #include "../resources/Pharaoh Walk Left/pharaoh_walk_left.h"
  #include "../resources/Pharaoh Walk Right/pharaoh_walk_right.h"

  xpm_image_t** sprites;
  xpm_image_t* current_image;

  pharaoh_animations = (animation*)malloc(sizeof(animation) * 10); //one for each direction

  //pharaoh idle up
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 2);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_up_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_up_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;

  pharaoh_animations[UP] = (animation){2, sprites};
  pharaoh_animations[IDLE_UP] = (animation){2, sprites};
  

  //pharaoh idle down
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 4);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_2, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[2] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_3, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[3] = current_image;

  pharaoh_animations[DOWN] = (animation){4, sprites};
  pharaoh_animations[IDLE_DOWN] = (animation){4, sprites};


  //pharaoh walk left
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 8);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_left_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_left_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_left_2, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[2] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_left_3, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[3] = current_image;
  if(xpm_load(pharaoh_walk_left_4, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[4] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_left_5, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[5] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_left_6, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[6] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_left_7, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[7] = current_image;

  pharaoh_animations[LEFT] = (animation){4, sprites};
  pharaoh_animations[DOWN_LEFT] = (animation){4, sprites};
  pharaoh_animations[UP_LEFT] = (animation){4, sprites};


  //pharaoh walk right
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 8);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_right_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_right_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_right_2, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[2] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_right_3, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[3] = current_image;
  if(xpm_load(pharaoh_walk_right_4, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[4] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_right_5, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[5] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_right_6, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[6] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_walk_right_7, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[7] = current_image;

  pharaoh_animations[RIGHT] = (animation){4, sprites};
  pharaoh_animations[DOWN_RIGHT] = (animation){4, sprites};
  pharaoh_animations[UP_RIGHT] = (animation){4, sprites};


  return 0;
}

int (load_animations)() {
  //for now, only the pharaoh animations
  if(load_pharaoh_animations()) return 1;
  return 0;
}
