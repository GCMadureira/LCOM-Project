#include "kbc.h"


int (read_kbc_command)(uint8_t* command){
  if(sys_outb(KBC_CMD_REG, RD_CMD_BYTE)) return 1;
  return util_sys_inb(KBC_OUT_REG, command);
}

int (write_kbc_command)(uint8_t command){
  return sys_outb(KBC_CMD_REG, command);
}

int (write_kbc_command_arg)(uint8_t arg){
  return sys_outb(KBC_CMDARG_REG, arg);
}

bool (valid_kbc_output)(bool aux){
  uint8_t status;
  if(util_sys_inb(KBC_STAT_REG, &status)) return false; //error reading status register
  if(status & (KBC_PAR_ERR | KBC_TO_ERR)) return false; //parity error or timeout error
  if(!(status & KBC_ST_OBF)) return false; //output buffer empty

  if(aux) return status & KBC_ST_AUX; //mouse data
  else return !(status & KBC_ST_AUX); //keyboard data
}

void (discard_kbc_output)(){
  uint8_t discard;
  util_sys_inb(KBC_OUT_REG, &discard);
}
