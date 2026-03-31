global FreeInterrupt2
extern ISRStub

FreeInterrupt2:
    cli
    push 0
    push 43
    jmp ISRStub