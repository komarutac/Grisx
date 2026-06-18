global SetCR2
SetCR2:
    mov ecx, [esp + 4]
    mov cr2, ecx
    mov eax, cr2
    ret