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

void htoa(unsigned char nChar, char* dst)	// converting a byte value to an ascii string 
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

int strcmp(const char* first, const char* second) // function compares two strings, params: 2 char pointers that points to a C style string
// returns 1 if equal or 0 if not
{	
	int first_len = strlen(first); // getting the length of the strings
	int second_len = strlen(second);
	
	if(first_len != second_len){ 
		return 0;
	}
	
	// the length of the strings must be equal here so it doesn't matter which I use for the "for" loop
	for(int i = 0; i < first_len; i++){ 
		if(first[i] != second[i]){
		return 0;
		}	
	}
	
	return 1; // if all characters are equal then return true
}

char atoh(char arr[])	// taking a string of 2 chars as parameter and return a single byte that represent the ascii chars but in hexadecimal,
{			// for example "2f" turn into 0x2f in one char
	for(int i = 0; i < 2; i++)
	{
		if(arr[i] >= '0' && arr[i] <= '9')	// if the char is between 0 to 9 then subtract 0x30
			arr[i] -= 0x30;
		else					// else the value should be between 'a' and 'f' and it subtracts by 0x57 
			arr[i] -= 0x57;	
	}
	char hex = 0;
	hex = arr[0] * 0x10;				// moving the most significant nibble to the most left bits by multiplying by 0x10
	hex += arr[1];					// adding the least significant nibble 
	return hex;
}













