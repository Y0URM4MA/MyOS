%ifndef PRINTING_ASM
%define PRINTING_ASM

print_string:      ;parameter: address of the desired string to be printed

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
	
	[BITS 32]

VIDEO_MEMORY equ 0xb8000
ATTRIBUTES db 0x0f

	;prints null-terminated string in protected mode using memory
	;parametrs: address of first char in string
print_string32:	
	push ebp
	mov ebp,esp
	push edx
	push esi
	push eax
	mov edx,VIDEO_MEMORY	;VGA address
	mov ah,[ATTRIBUTES]	;background and foreground colors
	mov esi,[ebp+8] ;[ebp+8] is the address of first string char
print:
	lodsb		;AL has now the ascii char
	cmp al,0	
	je done
	mov [edx],ax
	add edx,2
	jmp print
done:
	pop eax
	pop esi
	pop edx
	pop ebp
	ret 4
	
%endif	 
