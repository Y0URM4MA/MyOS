#ifndef _ISR_H
#define _ISR_H

typedef struct registers
{
   unsigned int gs,fs,es,ds;			// segment registers
   unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pushad.
   unsigned int int_no, err_code;    // Interrupt number and error code (if exists)
   unsigned int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t; 

void pic_init(); // This functions initiates the pic according to the setting I want (see implementation in isr.c for explanation)

void isr_handler(registers_t *r);

void irq_handler(registers_t *r);

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void *handler);

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void isr32(void);
extern void isr33(void);
extern void isr34(void);
extern void isr35(void);
extern void isr36(void);
extern void isr37(void);
extern void isr38(void);
extern void isr39(void);
extern void isr40(void);
extern void isr41(void);
extern void isr42(void);
extern void isr43(void);
extern void isr44(void);
extern void isr45(void);
extern void isr46(void);
extern void isr47(void);

#endif
