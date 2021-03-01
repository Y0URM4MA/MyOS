#ifndef _PIT_H
#define _PIT_H
#include <isr.h>

void PIT_init(unsigned int frequency);
void timer_handler(registers_t* r);
void sleep(int ticks);

#endif
