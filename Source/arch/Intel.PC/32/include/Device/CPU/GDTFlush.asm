;http://www.osdever.net/bkerndev/Docs/gdt.htm
global GDTFlush
extern GP

GDTFlush:
    lgdt [GP]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush
flush:
	ret