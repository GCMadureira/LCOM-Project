#ifndef _KBC_H_
#define _KBC_H_

#include <lcom/lcf.h>
#include "i8042.h"

int (kbc_write_command)(uint8_t command);
int (kbc_write_command_arg)(uint8_t arg);
int (kbc_read_command)(uint8_t* command);

bool (kbc_valid_output)(bool aux);
void (kbc_discard_output)();

#endif /* _KBC_H */
