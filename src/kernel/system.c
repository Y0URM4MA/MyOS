#include "system.h"

// Copies memory from src to dest with a count value that will indicate how many bytes to copy
void memcpy(unsigned char* dest, const unsigned char* src, unsigned int count){
	for(unsigned int i = 0; i<count; i++){
		*(dest+i)=*(src+i);
	}
}

// sets memory to dest with the value of "val", "count" bytes
void memset(unsigned char* dest, unsigned char val, unsigned int count){
	for(unsigned int i = 0; i<count; i++){
		*(dest+i)=val;
	}
}

// sets memory to dest with the value of "val", "count" words
void memsetw(unsigned short* dest, unsigned short val, unsigned int count){
	for(unsigned int i = 0 ; i<count; i++){
	*(dest+i)=val;
	}
}

// returns the length of a string given as a parameter
unsigned int strlen(const char* str){
	unsigned int len = 0;
	while((int)(*str)!=0){
		len++;
		str++;
	}
	return len;
} 

// uses inline assembly to perform an "in" command to get byte size information from port "port"
unsigned char port_byte_in(unsigned short port){
	unsigned char result;
	
	asm volatile("in %%dx,%%al" : "=a" (result) : "d" (port));
	return result;
}

// uses inline assembly to put a byte size value "data" to port "port"
void port_byte_out(unsigned short port, unsigned char data){
	asm volatile("out %%al, %%dx"  : : "d" (port), "a" (data));
}

// uses inline assembly to perform an "in" command to get word size information from port "port"
unsigned short port_word_in(unsigned short port){
	unsigned short result;
	asm volatile("in %%dx,%%ax" : "=a" (result) : "d" (port));
	return result;
}

// uses inline assembly to put a word size value "data" to port "port"
void port_word_out(unsigned short port, unsigned short data){
	asm volatile("out %%ax, %%dx"  : : "d" (port), "a" (data));
}

void htoa(unsigned char nChar, char* dst)
{
    dst[0] = nChar / 0x10;
    dst[1] = nChar % 0x10;
    dst[2] = 0;

    for (int i = 0; i < 2; i++)
        if (dst[i] >= 0 && dst[i] <= 9)
            dst[i] += 0x30;
        else
            dst[i] += 0x37;
            
}
















