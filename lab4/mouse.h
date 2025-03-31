#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <lcom/lcf.h>
#include "keyboard.h"
#include "i8042.h"

int (mouse_subscribe_int_exclusive)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();


#endif /* _MOUSE_H_ */