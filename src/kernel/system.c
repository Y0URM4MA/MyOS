#include "system.h"

void memcpy(unsigned char* dest, const unsigned char* src, unsigned int count){
	for(unsigned int i = 0; i<count; i++){
		*(dest+i)=*(src+i);
	}
}

void memset(unsigned char* dest, unsigned char val, unsigned int count){
	for(unsigned int i = 0; i<count; i++){
		*(dest+i)=val;
	}
}

void memsetw(unsigned short* dest, unsigned short val, unsigned int count){
	for(unsigned int i = 0 ; i<count; i++){
	*(dest+i)=val;
	}
}


unsigned int strlen(const char* str){
	unsigned int len = 0;
	while((int)(*str)!=0){
		len++;
		str++;
	}
	return len;
} 

unsigned char port_byte_in(unsigned short port){
	unsigned char result;
	
	asm volatile("in %%dx,%%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(unsigned short port, unsigned char data){
	asm volatile("out %%al, %%dx"  : : "d" (port), "a" (data));
}

unsigned short port_word_in(unsigned short port){
	unsigned short result;
	asm volatile("in %%dx,%%ax" : "=a" (result) : "d" (port));
	return result;
}

void port_word_out(unsigned short port, unsigned short data){
	asm volatile("out %%ax, %%dx"  : : "d" (port), "a" (data));
}




