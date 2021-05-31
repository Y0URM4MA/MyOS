#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <isr.h>

unsigned char kybrd_enc_value(void);
void kybrd_ctrl_cmd(unsigned char cmd);
void kybrd_enc_cmd(unsigned char cmd);
void keyboard_handler(registers_t* r);
void kybrd_init(void);
void buffer_clear(void);
char get_last_char(void);



#endif

