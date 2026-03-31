org 0x7C00
bits 16
%include "arch/i486/bootloader/BiosPrint.asm"

B16Start:
	xor ax, ax
	mov ds, ax
	mov ss, ax
	mov sp, 0x9C00
	xor ax, ax
	mov ds, ax
	cld
	BiosPrint StartMsg, A
	BiosPrint PMMsg, C
	BiosPrint BootMsg, D
	BiosPrint FailMsg, B
	cli
	hlt

StartMsg db "Reading boot disk sectors..." , 13, 10, 0
PMMsg db "Preparing kernel..." , 13, 10, 0
BootMsg db "Booting kernel..." , 13, 10, 0
FailMsg db "Failed to load kernel." , 13, 10, 0
times 510 - ($-$$) db 0
dw 0x0AA55