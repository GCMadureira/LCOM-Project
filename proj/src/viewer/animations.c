#include "animations.h"

animation* pharaoh_animations;
animation* enemy_animations;


enum animation_direction (entity_get_direction)(entity* entity) {
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


int (animations_clean)() {
  for(int i = 0; i < 10; ++i) {
    animation_destroy(pharaoh_animations[i]);
    animation_destroy(enemy_animations[i]);
  }

  free(pharaoh_animations);
  free(enemy_animations);

  return 0;
}

int (animation_destroy)(animation animation) {
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
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 8);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_up_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  sprites[1] = current_image;
  sprites[2] = current_image;
  sprites[3] = current_image;

  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_up_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[4] = current_image;
  sprites[5] = current_image;
  sprites[6] = current_image;
  sprites[7] = current_image;

  pharaoh_animations[UP] = (animation){8, sprites};
  pharaoh_animations[IDLE_UP] = (animation){8, sprites};
  
  //pharaoh idle down
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 16);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  sprites[1] = current_image;
  sprites[2] = current_image;
  sprites[3] = current_image;

  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[4] = current_image;
  sprites[5] = current_image;
  sprites[6] = current_image;
  sprites[7] = current_image;

  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_2, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[8] = current_image;
  sprites[9] = current_image;
  sprites[10] = current_image;
  sprites[11] = current_image;

  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(pharaoh_idle_down_3, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[12] = current_image;
  sprites[13] = current_image;
  sprites[14] = current_image;
  sprites[15] = current_image;

  pharaoh_animations[DOWN] = (animation){16, sprites};
  pharaoh_animations[IDLE_DOWN] = (animation){16, sprites};


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
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
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

  pharaoh_animations[LEFT] = (animation){8, sprites};
  pharaoh_animations[DOWN_LEFT] = (animation){8, sprites};
  pharaoh_animations[UP_LEFT] = (animation){8, sprites};


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
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
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

  pharaoh_animations[RIGHT] = (animation){8, sprites};
  pharaoh_animations[DOWN_RIGHT] = (animation){8, sprites};
  pharaoh_animations[UP_RIGHT] = (animation){8, sprites};


  return 0;
}


static int (load_enemy_animations)() {
  #include "../resources/Enemy 1 Walk Right/enemy1_walk_right.h"
  #include "../resources/Enemy 1 Walk Left/enemy1_walk_left.h"

  xpm_image_t** sprites;
  xpm_image_t* current_image;

  enemy_animations = (animation*)malloc(sizeof(animation) * 10); //one for each direction

  //enemy walk left
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 8);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_2, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[2] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_3, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[3] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_4, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[4] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_5, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[5] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_6, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[6] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_left_7, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[7] = current_image;

  enemy_animations[LEFT] = (animation){8, sprites};
  enemy_animations[DOWN_LEFT] = (animation){8, sprites};
  enemy_animations[UP_LEFT] = (animation){8, sprites};

  //enemy walk right
  sprites = (xpm_image_t**)malloc(sizeof(xpm_image_t*) * 8);
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_0, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[0] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_1, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[1] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_2, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[2] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_3, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[3] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_4, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[4] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_5, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[5] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_6, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[6] = current_image;
  current_image = (xpm_image_t*)malloc(sizeof(xpm_image_t));
  if(xpm_load(enemy1_walk_right_7, XPM_8_8_8_8, current_image) == NULL) return 1;
  sprites[7] = current_image;

  enemy_animations[RIGHT] = (animation){8, sprites};
  enemy_animations[DOWN_RIGHT] = (animation){8, sprites};
  enemy_animations[UP_RIGHT] = (animation){8, sprites};

  // For now, use the same animations for the rest of the directions
  enemy_animations[UP] = enemy_animations[RIGHT];
  enemy_animations[DOWN] = enemy_animations[RIGHT];
  enemy_animations[IDLE_DOWN] = enemy_animations[RIGHT];
  enemy_animations[IDLE_UP] = enemy_animations[RIGHT];

  return 0;
}

int (animations_load)() {
  // Load pharaoh & enemy animations
  if(load_pharaoh_animations()) return 1;
  if(load_enemy_animations()) return 1;
  return 0;
}
