#ifndef _EVENTS_PROJ_H_
#define _EVENTS_PROJ_H_

#include <lcom/lcf.h>
#include "../macros/scancodes.h"
#include "../drivers/mouse.h"
#include "../drivers/keyboard.h"

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

void (handle_mouse_event)();
void (handle_keyboard_event)();
int (get_next_event)(input_event* next_event);
int (clear_events)();

#endif /*_EVENTS_PROJ_H_ */
