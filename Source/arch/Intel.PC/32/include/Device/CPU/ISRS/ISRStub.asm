global ISRStub
extern ISRHandler

ISRStub:
    pusha
    push ax
    push cx
    push dx
    push bx
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, ISRHandler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    pop bx
    pop dx
    pop cx
    pop ax
    popa
    add esp, 8
    iret