/*
* Simulated Single Board Computer, (c) 2020 Christopher A. Bohn
*
* Student: <Aryan Timla>
*/

#include "ssbc.h"

pthread_mutex_t *mutex;
uint32_t *display_controls;
uint8_t *toggle_control;
uint16_t *keypad_control;
int running = 1;

int main() {
  ssbc_launch();
  uint8_t letters[] = {0x3F,0x3,0x6D,0x67,0x53,0x76,0x7E,0x23,0x7F,0x77}; //0-9
  mutex = ssbc_get_mutex();
  display_controls = ssbc_get_7_segment_address();
  toggle_control = ssbc_get_toggle_address();
  keypad_control = ssbc_get_keypad_address();
  keypad_control += 1;

  while (running) {
    pthread_mutex_lock(mutex);
    uint8_t toggle_positions = *toggle_control;
    uint8_t number = *keypad_control & 0x0Fu;
    pthread_mutex_unlock(mutex);
    if(toggle_positions & 0x8u || toggle_positions & 0x1u){
      if (toggle_positions & 0x8u) {   //leftmost toggle switch on
        pthread_mutex_lock(mutex);
        uint32_t character_in_position = (uint32_t)(letters[2]) << 8*3;  //2
        uint32_t character_in_position2 = (uint32_t)(letters[3]) << 8*2; //3
        uint32_t character_in_position3 = (uint32_t)(letters[1]) << 8;   //1
        *display_controls = (*display_controls) | character_in_position | character_in_position2 | character_in_position3;
        pthread_mutex_unlock(mutex);
      } else{
        *display_controls = (*display_controls) & 0xFFu;
      }
      if (toggle_positions & 0x1u) {   //rightmost toggle switch on
          pthread_mutex_lock(mutex);
          uint32_t character_in_position = (uint32_t)(letters[number]);
          *display_controls = (*display_controls) & 0xFFFFFF00u;
          *display_controls = (*display_controls) | character_in_position;
          pthread_mutex_unlock(mutex);
      }
      else{
        *display_controls = (*display_controls) & 0xFFFFFF00u;
      }
    } else{
      pthread_mutex_lock(mutex);
      uint32_t clear_position = 0x0;
      *display_controls = *display_controls & clear_position;
      pthread_mutex_unlock(mutex);
    }
  }
  ssbc_terminate();
  return 0;
}
