#ifndef _IDT_H
#define _IDT_H

//	A struct for defining an IDT entry 

typedef struct
{
	unsigned short offset_low; //	offset bits 0...15
	unsigned short selector;	// code segment selector in gdt
	unsigned char zero_byte;	// unused byte
	unsigned char attributes;
	unsigned short offset_high; // offset bits 16...31
}__attribute__((packed)) idt_entry_struct;


typedef struct
{
	unsigned short size;	// size of idt minus 1
	unsigned int base;		// base address of idt
}__attribute__((packed)) idt_ptr_struct;


void make_idt_gate(unsigned char count, unsigned int offset, unsigned char attr);
void make_idt();

idt_entry_struct idt_entries[256];
idt_ptr_struct IDTR;

#endif


