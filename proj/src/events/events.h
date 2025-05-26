#ifndef _EVENTS_PROJ_H_
#define _EVENTS_PROJ_H_

#include <lcom/lcf.h>

#include "../macros/scancodes.h"
#include "../drivers/mouse.h"
#include "../drivers/keyboard.h"
#include "../model/structs.h"

void (event_handle_mouse)();
void (event_handle_keyboard)();
int (events_get_next)(input_event* next_event);
int (events_clear)();

#endif /*_EVENTS_PROJ_H_ */
