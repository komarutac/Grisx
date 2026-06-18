global SetCR0
SetCR0:
    mov ecx, [esp + 4]
    mov cr0, ecx
    mov eax, cr0
    ret