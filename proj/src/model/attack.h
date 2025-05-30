#ifndef _ATTACK_PROJ_H_
#define _ATTACK_PROJ_H_

#include <lcom/lcf.h>
#include <math.h>

#include "../drivers/drivers.h"
#include "../viewer/animations.h"
#include "../viewer/static_images.h"
#include "structs.h"


attack* (attack_create_full)(double pos_x, double pos_y, double speed_x, double speed_y, uint32_t damage, uint32_t frames, animation animation);
int (attack_destroy)(attack* attack);

void (attack_move)(attack* attack);

void (attack_node_destroy)(attack_node* node);
void (attack_list_add)(attack_node** list, attack* attack);
void (attack_list_destroy)(attack_node* list);

#endif /*_ATTACK_PROJ_H_ */
