[BITS 16]
[ORG 0x7c00]

KERNEL_OFFSET equ 0x7e00

xor ax,ax 			;making ax equal to 0
mov ds,ax			;resetting segments just to make sure we're not messing up with adresses
mov es,ax
cli				;we don't want interrupts while changing ss:sp of course
mov ss,ax
mov sp,0x7c00
mov bp,sp			;setting up stack, memory below it is free to use
sti
mov [drive_number],dl
push real_mode_msg
call print_string
call disk_load
jmp switch_pm
jmp $


;-----------------------
; Includes/Functions
;-----------------------
%include "printing.asm"
%include "gdt.asm"
%include "load_kernel.asm"
%include "switch_to_pm.asm"	

[BITS 32]
PM:
	push prot_mode_msg
	call print_string32
	call KERNEL_OFFSET 
	jmp $
	
;-----------------------
; data start here
;-----------------------

real_mode_msg db "Started in Real Mode",0
prot_mode_msg db "Got into Protected Mode successfully",0
drive_number db 0	
DISK_ERROR_MSG db "Error reading disk, please try to turn of your pc and boot it again",13,10,0


TIMES 510-($-$$) db 0  			;filling up the rest of the boot sector with zeros 
dw 0xAA55				;MBR signature for old BIOSes to know where the MBR ends,
					;today there are UEFIs that can handle loading the MBR without this signature
