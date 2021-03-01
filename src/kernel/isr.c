#include <isr.h>
#include <system.h>
#include <screen.h>

//variables:
static unsigned char *const exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow (INTO instruction)",
    "Bounds check (BOUND instruction)",
    "Invalid opcode",
    "Coprocessor not available",
    "Double fault",
    "Reserved",
    "Invalid TSS",
    "Segment not present",
    "Stack exception",
    "General protection",
    "Page fault",
    "Reserved",
    "Coprecessor error",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/* This array is an array of function pointers. I use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void pic_init(){
	//ICW1 bits:
    	//Bit 0 - Set to 1 so I can send ICW 4
    	//Bit 1 - PIC cascading bit. x86 architectures have 2 PICs, so I need the primary PIC cascaded with the slave. I Keep it 0 for that
    	//Bit 2 - CALL address interval. Ignored by x86 and kept at 8, so I keep it 0
    	//Bit 3 - Edge triggered/Level triggered mode bit. By default, we are in edge triggered, so I set it to 0
    	//Bit 4 - Initialization bit. Set to 1
    	//Bits 5-7 - Unused on x86, set to 0.
	port_byte_out((unsigned short)0x20,(unsigned char)0x11);
	port_byte_out((unsigned short)0xa0,(unsigned char)0x11);
	
	//ICW2 - remapping the IRQs to offset 32-47 in the IDT
	port_byte_out((unsigned short)0x21,(unsigned char)0x20);
	port_byte_out((unsigned short)0xa1,(unsigned char)0x28);
	
	//ICW3 - which IRQ uses the master PIC to communicate with the slave PIC
	port_byte_out((unsigned short)0x21,(unsigned char)0x04); //tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	port_byte_out((unsigned short)0xa1,(unsigned char)0x02); //tell Slave PIC its cascade identity (0000 0010)
	
	//ICW4 bits:
	//Bit 0 - If set (1), it is in 80x86 mode. Cleared if MCS-80/85 mode
	//Bit 1 - If set, controller automatically performs End of Interrupt (EOI) operation
	//Bit 2 - Only use if BUF is set. If set (1), selects buffer master. Cleared if buffer slave.
	//Bit 3 - If set, controller operates in buffered mode
	//Bit 4 - Special Fully Nested Mode. Used in systems with a large amount of cascaded controllers.
	//Bits 5-7 - Reserved, must be 0
	port_byte_out((unsigned short)0x21,(unsigned char)0x01);
	port_byte_out((unsigned short)0xa1,(unsigned char)0x01);
	
	//nulling the ports enabling interrupts
	port_byte_out((unsigned short)0x21,(unsigned char)0x00);
	port_byte_out((unsigned short)0xa1,(unsigned char)0x00);
}	
	
void isr_handler(registers_t *r){

if (r->int_no < 32){
        // Display the description for the Exception that occurred and then loop for ever
        kprint("Exception Occurred!: ");
        kprint(exception_messages[r->int_no]);
        for (;;);
    }	

}

// This installs a custom IRQ handler for the given IRQ 
void irq_install_handler(int irq, void *handler)
{
    irq_routines[irq] = handler;
}

// This uninstalls the custom IRQ handler from the given IRQ
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}


void irq_handler(registers_t *r)
{
    void (*handler)(registers_t* r) = irq_routines[r->int_no - 32];
    if(handler)
    {
    	handler(r);
    }
    if(r->int_no - 32 >=8 && r->int_no < 16)
    {
    	port_byte_out(0xA0,0x20);
    }
    
    port_byte_out(0x20,0x20);

}























