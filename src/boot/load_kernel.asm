mov [driveNumber],dl		;saving the drive number in variable, when BIOS loads the bootloader it saves the drive number in dl for further usage                    
int 0x13 			;ah already equals to 0, resseting the disk system, and pulling heads to track 0.
mov ah,2			;setting ah to alert that the interrupt will read from disk.
mov al,1			;setting the number of sectors to read.
mov ch,0			;setting the track number to read from.
mov cl,2			;setting the sector number to read from.
mov dh,0			;setting the head number.
mov bx,0x7e00			;es:bx is the address in ram where the interrupt will load the kernel to. 
int 0x13
jc DISK_ERROR
jmp 0x7e00
DISK_ERROR:
push DISK_ERROR_MSG
call print_string
jmp $

;-----------------------
; data start here
;-----------------------

driveNumber db 0	
DISK_ERROR_MSG db "Error reading disk, please try to turn of your pc and boot it again",13,10,0

;-----------------------
; functions start here
;-----------------------
%include "printing.asm"	
