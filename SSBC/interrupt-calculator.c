/*
* Simulated Single Board Computer, (c) 2020 Christopher A. Bohn
*
* Student: <Aryan Timla>
* Evaluate for bonus credit: <yes>
*/

#include "ssbc.h"
#include <stdio.h>

pthread_mutex_t *mutex;
uint32_t *display_controls;
uint8_t *toggle_control;
uint16_t *keypad_control;
int running = 1;

uint32_t inttobinary(int n){
  uint32_t letter[] = {0x3F,0x3,0x6D,0x67,0x53,0x76,0x7E,0x23,0x7F,0x77}; //0-9
  uint32_t th = letter[n / 1000];
  uint32_t h = letter[(n%1000)/100];
  uint32_t tens = letter[(n%100)/10];
  uint32_t ones = letter[n%10];

  if(n < 1000){
    th = 0;
  }
  if(n < 100){
    h = 0;
  }
  if(n < 10){
    tens = 0;
  }
  uint32_t character_in_position = (uint32_t)(th) << 8*3;     //1000th place
  uint32_t character_in_position2 = (uint32_t)(h) << 8*2;     //100
  uint32_t character_in_position3 = (uint32_t)(tens) << 8;    //10th place
  uint32_t character_in_position4 = (uint32_t)(ones);         //1s place

  return character_in_position | character_in_position2 | character_in_position3 | character_in_position4;
}

void signal_handler(int sig) {
  // if (sig == *keypad_control & 0x0Fu)
    printf("CAUGHT Signal %d\n", sig);
}

int main() {
  ssbc_launch();
  uint8_t letters[] = {0x3F,0x3,0x6D,0x67,0x53,0x76,0x7E,0x23,0x7F,0x77}; //0-9
  mutex = ssbc_get_mutex();
  display_controls = ssbc_get_7_segment_address();
  toggle_control = ssbc_get_toggle_address();
  keypad_control = ssbc_get_keypad_address();
  keypad_control += 1;
  *display_controls = (*display_controls) & 0x00;

  int operand1 = 0;
  int operand2 = 0;
  sigset(SIGUSR1,signal_handler);

  while (running) {
    pthread_mutex_lock(mutex);
    uint8_t toggle_positions = *toggle_control;
    uint8_t number = *keypad_control & 0x0Fu;
    pthread_mutex_unlock(mutex);
    if(toggle_positions & 0x8u || toggle_positions & 0x4u || toggle_positions & 0x2u || toggle_positions & 0x1u){
      if (toggle_positions & 0x8u) {   //leftmost toggle switch on 'a'
      pthread_mutex_lock(mutex);
      *display_controls = (*display_controls) | (uint32_t)(letters[0]);
        *display_controls = *display_controls & 0x0;
        operand1 = operand1 * 10 + number;
        *display_controls = inttobinary(operand1);
      pthread_mutex_unlock(mutex);
      }

    if (toggle_positions & 0x4u) {   //'s' on
    pthread_mutex_lock(mutex);
      *display_controls = (*display_controls) | (uint32_t)(letters[0]);
      *display_controls = *display_controls & 0x0;
      operand2 = operand2 * 10 + number;
      *display_controls = inttobinary(operand2);
    pthread_mutex_unlock(mutex);
    }

    if (toggle_positions & 0x2u) {   //right toggle switch on 'd'
    pthread_mutex_lock(mutex);
    int sum = (operand1 + operand2);
    *display_controls = (*display_controls) & (uint32_t)(letters[0]);
    *display_controls = inttobinary(sum);
    if (sum > 9999) {   //edge case
      uint32_t error = (uint32_t)(0x7C) << 8*2; //E
      uint32_t error1 = (uint32_t)(0x48) << 8;   //r
      uint32_t error2 = (uint32_t)(0x48);   //r
      *display_controls = error | error1 | error2;
    }
    pthread_mutex_unlock(mutex);
    }

    if (toggle_positions & 0x1u) {   //rightmost toggle switch on 'f'
    pthread_mutex_lock(mutex);
    int difference = (operand1 - operand2);
    *display_controls = (*display_controls) | (uint32_t)(letters[0]);
    *display_controls = inttobinary(difference);
    if (difference < 0) { //edge case
      uint32_t error = (uint32_t)(0x7C) << 8*2; //E
      uint32_t error1 = (uint32_t)(0x48) << 8;   //r
      uint32_t error2 = (uint32_t)(0x48);   //r
      *display_controls = error | error1 | error2;
    }
    pthread_mutex_unlock(mutex);
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
