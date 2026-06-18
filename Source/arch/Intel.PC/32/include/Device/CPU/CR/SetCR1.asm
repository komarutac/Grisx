global SetCR1
SetCR1:
    mov ecx, [esp + 4]
    mov cr1, ecx
    mov eax, cr1
    ret