global SetCR3
SetCR3:
    mov ecx, [esp + 4]
    mov cr3, ecx
    mov eax, cr3
    ret