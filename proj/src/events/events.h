#ifndef _EVENTS_PROJ_H_
#define _EVENTS_PROJ_H_

#include <lcom/lcf.h>

#include "../macros/scancodes.h"
#include "../drivers/mouse.h"
#include "../drivers/keyboard.h"
#include "../model/structs.h"

void (handle_mouse_event)();
void (handle_keyboard_event)();
int (get_next_event)(input_event* next_event);
int (clear_events)();

#endif /*_EVENTS_PROJ_H_ */
