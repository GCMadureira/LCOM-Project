#include "events.h"

static input_event_node* input_event_list = NULL;



static uint8_t packet_bytes[3];
static int state = 0; //0 means first byte, 1 means second by, 2 means third byte
void (handle_mouse_event)() {
  if(!valid_kbc_output(true)){ // check if the output buffer has valid data
    discard_kbc_output(); // discard if not
    return;
  }
  else mouse_ih(); // handle interrupt if yes

  uint8_t packet_byte = get_mouse_packet_byte();

  // the first byte always has the bit 3 on, skip byte if it does not for synchronization
  if(state == 0 && !(packet_byte & BIT(3))) return;

  packet_bytes[state] = packet_byte;

  if(state == 2){
    struct packet packet = assemble_packet(packet_bytes);

    input_event new_event;
    new_event.event_type = MOUSE_EVENT;
    new_event.mouse_packet = packet;
    
    input_event_node* new_event_node = (input_event_node*)malloc(sizeof(input_event_node));
    new_event_node->event = new_event;
    new_event_node->next_event = NULL;

    if(input_event_list == NULL) input_event_list = new_event_node;
    else input_event_list->next_event = new_event_node;
  }
  state = (state + 1) % 3;
}


static bool extended_flag = false;
void (handle_keyboard_event)() {
  if(!valid_kbc_output(false)){ //check if the output buffer has valid data
    discard_kbc_output(); //discard if not
    return;
  }
  else kbc_ih(); // handle interrupt if yes

  uint8_t scancode_nbytes;
  uint8_t scancode_byte1 = 0, scancode_byte2 = 0;

  if(get_scancode() == EXTENDED_SCANCODE) { //wait for next interrupt
    extended_flag = true;
    return;
  }
  else if(extended_flag){ //received the second byte
    scancode_nbytes = 2;
    scancode_byte1 = EXTENDED_SCANCODE;
    scancode_byte2 = get_scancode();
    extended_flag = false;
  }
  else { //one byte scancode
    scancode_nbytes = 1;
    scancode_byte1 = get_scancode();
  }

  input_event new_event;
  new_event.event_type = KEYBOARD_EVENT;
  new_event.scancode_nbytes = scancode_nbytes;
  new_event.scancode_byte1 = scancode_byte1;
  new_event.scancode_byte2 = scancode_byte2;

  input_event_node* new_event_node = (input_event_node*)malloc(sizeof(input_event_node));
  new_event_node->event = new_event;
  new_event_node->next_event = NULL;

  if(input_event_list == NULL) input_event_list = new_event_node;
  else input_event_list->next_event = new_event_node;
}

int (get_next_event)(input_event* next_event) {
  if(input_event_list == NULL) return 1;

  input_event_node* victim_node = input_event_list;
  memcpy(next_event, &(input_event_list->event), sizeof(input_event));
  input_event_list = input_event_list->next_event;
  free(victim_node);

  return 0;
}

int (clear_events)() {
  while(input_event_list != NULL) {
    input_event_node* victim_node = input_event_list;
    input_event_list = input_event_list->next_event;
    free(victim_node);
  }
  return 0;
}
