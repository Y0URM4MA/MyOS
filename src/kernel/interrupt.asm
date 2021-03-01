[GLOBAL isr0]
[GLOBAL isr1]
[GLOBAL isr2]
[GLOBAL isr3]
[GLOBAL isr4]
[GLOBAL isr5]
[GLOBAL isr6]
[GLOBAL isr7]
[GLOBAL isr8]
[GLOBAL isr9]
[GLOBAL isr10]
[GLOBAL isr11]
[GLOBAL isr12]
[GLOBAL isr13]
[GLOBAL isr14]
[GLOBAL isr15]
[GLOBAL isr16]
[GLOBAL isr17]
[GLOBAL isr18] 
[GLOBAL isr19]
[GLOBAL isr20]
[GLOBAL isr21]
[GLOBAL isr22]
[GLOBAL isr23]
[GLOBAL isr24]
[GLOBAL isr25]
[GLOBAL isr26]
[GLOBAL isr27]
[GLOBAL isr28]
[GLOBAL isr29]
[GLOBAL isr30]
[GLOBAL isr31]
[GLOBAL isr32]
[GLOBAL isr33]
[GLOBAL isr34]
[GLOBAL isr35]
[GLOBAL isr36]
[GLOBAL isr37]
[GLOBAL isr38]
[GLOBAL isr39]
[GLOBAL isr40]
[GLOBAL isr41]
[GLOBAL isr42]
[GLOBAL isr43]
[GLOBAL isr44]
[GLOBAL isr45]
[GLOBAL isr46]
[GLOBAL isr47]


[EXTERN isr_handler]
[EXTERN irq_handler]

irq_common_stub:
    pushad
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack for access to the registers structure in isr.h file
    push eax
    mov eax, irq_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP


isr_common_stub:
    pushad
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack for access to the registers structure in isr.h file
    push eax
    mov eax, isr_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

isr0: ;Division by zero error
    cli
    push byte 0    ; A normal ISR stub that pops a dummy error code to keep a
                   ; uniform stack frame    
    push byte 0
    jmp isr_common_stub

isr1: ;Debug exceptions
    cli
    push byte 0    
    push byte 1
    jmp isr_common_stub
              
isr2: ;Nonmaskable interrupt
    cli
    push byte 0    
    push byte 2
    jmp isr_common_stub
        
isr3: ;Breakpoint
    cli
    push byte 0    
    push byte 3
    jmp isr_common_stub
        
isr4: ;Overflow (INTO instruction)
    cli
    push byte 0    
    push byte 4
    jmp isr_common_stub
        
isr5: ;Bounds check (BOUND instruction)
    cli
    push byte 0    
    push byte 5
    jmp isr_common_stub
        
isr6: ;Invalid opcode
    cli
    push byte 0    
    push byte 6
    jmp isr_common_stub
        
isr7: ;Coprocessor not available
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub
        
isr8: ;Double fault
    cli
    push byte 8    ; I don't push a value on the stack in this one!
                   ; It pushes one already! Use this type of stub for exceptions
                   ; that pushes error codes!
    jmp isr_common_stub
    
isr9: ;(reserved)
    cli
    push byte 0    
    push byte 9
    jmp isr_common_stub
      
isr10: ;Invalid TSS
    cli   
    push byte 10
    jmp isr_common_stub
      
isr11: ;Segment not present
    cli    
    push byte 11
    jmp isr_common_stub
      
isr12: ;Stack exception
    cli  
    push byte 12
    jmp isr_common_stub
      
isr13: ;General protection
    cli   
    push byte 13
    jmp isr_common_stub
      
isr14: ;Page fault
    cli
    push byte 14
    jmp isr_common_stub
      
isr15: ;(reserved)
    cli
    push byte 0    
    push byte 15
    jmp isr_common_stub
      
isr16: ;Coprecessor error
    cli
    push byte 0    
    push byte 16
    jmp isr_common_stub
      
isr17:
    cli
    push byte 0    
    push byte 17
    jmp isr_common_stub
      
isr18: ;(reserved)
    cli
    push byte 0    
    push byte 18
    jmp isr_common_stub
      
isr19: ;(reserved)
    cli
    push byte 0    
    push byte 19
    jmp isr_common_stub
      
isr20: ;(reserved)
    cli
    push byte 0    
    push byte 20
    jmp isr_common_stub
      
isr21: ;(reserved)
    cli
    push byte 0    
    push byte 21
    jmp isr_common_stub
      
isr22:
    cli
    push byte 0    
    push byte 22
    jmp isr_common_stub
      
isr23:
    cli
    push byte 0    
    push byte 23
    jmp isr_common_stub
      
isr24: ;(reserved)
    cli
    push byte 0    
    push byte 24
    jmp isr_common_stub
      
isr25: ;(reserved)
    cli
    push byte 0    
    push byte 25
    jmp isr_common_stub
      
isr26: ;(reserved)
    cli
    push byte 0    
    push byte 26
    jmp isr_common_stub
      
isr27: ;(reserved)
    cli
    push byte 0    
    push byte 27
    jmp isr_common_stub
      
isr28: ;(reserved)
    cli
    push byte 0    
    push byte 28
    jmp isr_common_stub
      
isr29: ;(reserved)
    cli
    push byte 0    
    push byte 29
    jmp isr_common_stub
      
isr30: ;(reserved)
    cli
    push byte 0    
    push byte 30
    jmp isr_common_stub
      
isr31: ;(reserved)
    cli
    push byte 0    
    push byte 31
    jmp isr_common_stub
    

; IRQ wrappers, there are two PICs so there are 16 wrappers

isr32: ;IRQ 0 - System timer
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub
    
isr33: ;IRQ 1 - keyboard
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub
    
isr34: ;IRQ 2 - cascaded signals from IRQs 8–15
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub
    
isr35:	;IRQ 3
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub
    
isr36:	;IRQ 4
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub
    
isr37:	;IRQ 5
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub
    
isr38:	;IRQ 6 – floppy disk controller
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub
    
isr39:	
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub
    
isr40:
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub
    
isr41:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub
    
isr42:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub
    
isr43:
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub
    
isr44:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub
    
isr45:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub
    
isr46:	;IRQ 14 – primary ATA channel 
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub
    
isr47:	;IRQ 15 – secondary ATA channel
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub
        
    

    
    
    
      
    
        


