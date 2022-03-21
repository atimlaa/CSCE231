/*
 * Simulated Single Board Computer, (c) 2020 Christopher A. Bohn
 */

#define _XOPEN_SOURCE 500
#include <signal.h>
#include <pthread.h>
#include <stdint.h>

#ifndef SSBC_SSBC_H
#define SSBC_SSBC_H

void ssbc_launch();
void ssbc_terminate();
pthread_mutex_t *ssbc_get_mutex();

int ssbc_print(const char *fmt, ...);

void *ssbc_get_keypad_address();
void *ssbc_get_toggle_address();
void *ssbc_get_7_segment_address();
//void *ssbc_get_LED_address();

#endif //SSBC_SSBC_H
