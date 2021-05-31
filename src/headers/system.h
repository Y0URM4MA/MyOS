#ifndef _SYSTEM_H
#define _SYSTEM_H
 
void memcpy(unsigned char* dest, const unsigned char* src, unsigned int count);
void memset(unsigned char* dest, unsigned char val, unsigned int count);
void memsetw(unsigned short* dest, unsigned short val, unsigned int count);
unsigned int strlen(const char* str);
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
void htoa(unsigned char nChar, char* dst);
int strcmp(const char* first, const char* second);
char atoh(char arr[]);

#endif
