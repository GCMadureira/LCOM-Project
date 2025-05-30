#ifndef _ARENA_PROJ_H_
#define _ARENA_PROJ_H_

#include <lcom/lcf.h>

#include "entity.h"
#include "structs.h"
#include "../events/events.h"
#include "../drivers/drivers.h"
#include "../controller/main_controller.h"


arena* (arena_create)();
int (arena_destroy)(arena* arena);


#endif /*_ARENA_PROJ_H_*/
