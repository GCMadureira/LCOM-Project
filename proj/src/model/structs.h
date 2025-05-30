#ifndef _STRUCTS_PROJ_H_
#define _STRUCTS_PROJ_H_

#include <lcom/lcf.h>

enum event_type {
  MOUSE_EVENT,
  KEYBOARD_EVENT
};

typedef struct {
  enum event_type event_type;
  union {
    struct {
      uint8_t scancode_nbytes;
      uint8_t scancode_byte1;
      uint8_t scancode_byte2;
    };
    struct packet mouse_packet;
  };
} input_event;

typedef struct _input_event_node input_event_node;
struct _input_event_node{
  input_event event;
  input_event_node* next_event;
};

typedef struct {
  uint32_t n_frames; //number of sprites in the animation
  xpm_image_t** sprites; //a pointer to an array of sprites
} animation;

typedef struct {
  double pos_x, pos_y;
  double speed_x, speed_y; // this vector gets normalized
  double speed_multiplier; //this is the real speed
  bool last_horizontal_direction; // right is true, left is false
  uint32_t health;
  animation* animations;
} entity;

typedef struct _entity_node entity_node;
struct _entity_node{
  entity* entity;
  entity_node* next_entity;
};

typedef struct {
  double pos_x, pos_y;
  double speed_x, speed_y;
  uint32_t frames; // the number of frames the attack is present
  uint32_t damage;
  animation animation;
} attack;

// useful when there are many attacks
typedef struct _attack_node attack_node;
struct _attack_node{
  attack* attack;
  attack_node* next_attack;
};

typedef struct {
  entity* player;
  entity* mouse;
  entity_node* enemies;
  attack_node* player_attacks;
  entity_node* hearts; 
  double pos_x, pos_y;
  xpm_image_t* background_image;
} arena;

typedef struct {
  int menu_status; // indicates which option is selected
  int num_options; // total num of options
  xpm_image_t** sprites;
  xpm_image_t* background_image;
} menu;

#endif /*_STRUCTS_PROJ_H_ */
