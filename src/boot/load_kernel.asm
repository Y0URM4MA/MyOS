%ifndef LOAD_KERNEL_ASM
%define LOAD_KERNEL_ASM
[BITS 16]
disk_load:
push bp
mov bp,sp
push ax
push cx
push dx
push bx
mov dl,[drive_number]	;saving the drive number in variable, when BIOS loads the bootloader it 									saves the drive number in dl for further usage                    
int 0x13 			;ah already equals to 0, resseting the disk system, and pulling heads to track 0.
mov ah,2			;setting ah to alert that the interrupt will read from disk.
mov al,15			;setting the number of sectors to read.
mov ch,0			;setting the track number to read from.
mov cl,2			;setting the sector number to read from.
mov dh,0			;setting the head number.
mov bx,0x7e00			;es:bx is the address in ram where the interrupt will load the kernel to. 
int 0x13
jc DISK_ERROR
jmp continue
DISK_ERROR:
push DISK_ERROR_MSG
call print_string
jmp $
continue:
pop bx
pop dx
pop cx
pop ax
pop bp
ret

%endif
