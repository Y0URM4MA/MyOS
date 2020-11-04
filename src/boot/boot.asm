[BITS 16]
[ORG 0x7c00]


xor ax,ax 			;making ax equal to 0
mov ds,ax			;resetting segments just to make sure we're not messing up with adresses
mov es,ax
cli				;we don't want interrupts while changing ss:sp of course
mov ss,ax
mov sp,0x7c00			;setting up stack, memory below it is free to use
sti

	
mov [driveNumber],dl		;saving the drive number in variable, when BIOS loads the bootloader it saves the drive number in dl for further usage                    
int 0x13 			;ah already equals to 0, resseting the disk system, and pulling heads to track 0.
mov ah,2			;setting ah to alert that the interrupt will read from disk.
mov al,1			;setting the number of sectors to read.
mov ch,0			;setting the track number to read from.
mov cl,2			;setting the sector number to read from.
mov dh,0			;setting the head number.
mov bx,0x7e00			;es:bx is the address in ram where the interrupt will load the kernel to. 
int 0x13
jmp 0x7e00

;-----------------------
; data start here
;-----------------------

driveNumber db 0	

;-----------------------
; functions start here
;-----------------------
	



TIMES 510-($-$$) db 0  			;filling up the rest of the boot sector with zeros 
dw 0xAA55				;MBR signature for old BIOSes to know where the MBR ends,
					;today there are UEFIs that can handle loading the MBR without this signature
