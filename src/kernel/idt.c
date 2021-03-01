#include <idt.h>
#include <system.h>
#include <isr.h>

idt_entry_struct idt_entries[256];
idt_ptr_struct IDTR;


void make_idt_gate(unsigned char count, unsigned int offset, unsigned char attr)
{	// look at idt.h to understand idt gate structure.
	idt_entries[count].offset_low = (unsigned short)offset;
	idt_entries[count].offset_high = (unsigned short)(offset>>16);
	idt_entries[count].selector = 0x0008;
	idt_entries[count].zero_byte = 0x0;
	idt_entries[count].attributes = attr;
}

void make_idt(void)
{
	IDTR.size = (sizeof idt_entries) - 1;
	IDTR.base = (unsigned int)&idt_entries;
	
	memset((unsigned char*)&idt_entries, 0, sizeof idt_entries);
	
	make_idt_gate((unsigned char)0, (unsigned int)isr0, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)1, (unsigned int)isr1, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)2, (unsigned int)isr2, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)3, (unsigned int)isr3, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)4, (unsigned int)isr4, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)5, (unsigned int)isr5, (unsigned char)0x8E);
   	make_idt_gate((unsigned char)6, (unsigned int)isr6, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)7, (unsigned int)isr7, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)8, (unsigned int)isr8, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)9, (unsigned int)isr9, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)10, (unsigned int)isr10, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)11, (unsigned int)isr11, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)12, (unsigned int)isr12, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)13, (unsigned int)isr13, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)14, (unsigned int)isr14, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)15, (unsigned int)isr15, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)16, (unsigned int)isr16, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)17, (unsigned int)isr17, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)18, (unsigned int)isr18, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)19, (unsigned int)isr19, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)20, (unsigned int)isr20, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)21, (unsigned int)isr21, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)22, (unsigned int)isr22, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)23, (unsigned int)isr23, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)24, (unsigned int)isr24, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)25, (unsigned int)isr25, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)26, (unsigned int)isr26, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)27, (unsigned int)isr27, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)28, (unsigned int)isr28, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)29, (unsigned int)isr29, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)30, (unsigned int)isr30, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)31, (unsigned int)isr31, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)32, (unsigned int)isr32, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)33, (unsigned int)isr33, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)34, (unsigned int)isr34, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)35, (unsigned int)isr35, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)36, (unsigned int)isr36, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)37, (unsigned int)isr37, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)38, (unsigned int)isr38, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)39, (unsigned int)isr39, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)40, (unsigned int)isr40, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)41, (unsigned int)isr41, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)42, (unsigned int)isr42, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)43, (unsigned int)isr43, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)44, (unsigned int)isr44, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)45, (unsigned int)isr45, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)46, (unsigned int)isr46, (unsigned char)0x8E);
    	make_idt_gate((unsigned char)47, (unsigned int)isr47, (unsigned char)0x8E);
    	
	asm volatile("lidtl (%0)" : : "r" (&IDTR));
	asm volatile("sti");
}	
