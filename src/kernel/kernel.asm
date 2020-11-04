[BITS 16]
[ORG 0x7e00]

push msg
call print_string
mov ax,dx
push ax
call print_hex_byte
xchg al,ah
push ax
call print_hex_byte
jmp $
hlt		;this makes a real system halt
ret     ;this makes qemu halt, to ensure everything works we add both
	
msg db "Hello World!",13,10,0	;null terminated string

;-----------------------
; functions start here
;-----------------------

print_string:
	push bp
	mov bp,sp
	push ax
	push bx
	push si
	mov ah,0x0e				;Teletype output when using int 0x10
	mov si,[bp+4]
	mov bx,0				;making sure we're printing on the current page
	Print:
		lodsb
		cmp al,0
		jz finish
		int 0x10
		jmp Print
	finish:
		pop si
		pop bx
		pop ax
		pop bp
		ret 2

	
print_hex_byte:                      ;parameter is 16 bit value but it prints only the most significant byte
	push bp
	mov bp,sp	
	push ax
	push bx
	mov ax,[bp+4]
	xchg al,ah
	xor bx,bx
	mov bh,al
	mov ah,0x0e
	shr al,4
	cmp al,0x0a
	jl below
	add al,0x37
	jmp con
	below:
		add al,0x30
	con:
	int 0x10
	mov al,bh
	and al,00001111b
	cmp al,0x0a
	jl below2
	add al,0x37
	jmp con2
	below2:
		add al,0x30
	con2:
	int 0x10
	pop bx
	pop ax
	pop bp
	ret 2		



TIMES 512-($-$$) db 0




