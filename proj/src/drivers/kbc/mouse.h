#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"

int (mouse_subscribe_int_exclusive)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();

uint8_t (mouse_get_packet_byte)();

int (mouse_stream_enable_data_reporting)();
int (mouse_stream_disable_data_reporting)();

struct packet (mouse_assemble_packet)(uint8_t packet_bytes[3]);


#endif /* _MOUSE_H_ */
