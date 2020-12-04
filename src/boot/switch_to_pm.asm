%ifndef SWITCH_TO_PM_ASM
%define SWITCH_TO_PM_ASM
[BITS 16]
switch_pm:
	cli
	lgdt [gdt_descriptor]
	mov eax,cr0
	or eax,0x1
	mov cr0,eax
	jmp CODE_SEG:START_PM

	
[BITS 32]
START_PM:
	mov ax,DATA_SEG
	mov ds,ax
	mov ss,ax
	mov es,ax
	mov gs,ax
	mov fs,ax
	mov ebp, 0x7c000
	mov esp,ebp
	jmp PM

%endif	
		
