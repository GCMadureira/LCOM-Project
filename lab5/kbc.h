#ifndef _KBC_H_
#define _KBC_H_

#include <lcom/lcf.h>
#include "i8042.h"

int (write_kbc_command)(uint8_t command);
int (write_kbc_command_arg)(uint8_t arg);
int (read_kbc_command)(uint8_t* command);

bool (valid_kbc_output)(bool aux);
void (discard_kbc_output)();

#endif /* _KBC_H */
