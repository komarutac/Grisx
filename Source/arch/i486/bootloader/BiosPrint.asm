%macro BiosPrint 2
	mov si, word %1
ch_loop%2:lodsb
	or al, al
	jz done%2
	mov ah, 0x0E
	int 0x10
	jmp ch_loop%2
done%2:
%endmacro