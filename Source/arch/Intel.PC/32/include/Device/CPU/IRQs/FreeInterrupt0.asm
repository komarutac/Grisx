global FreeInterrupt0
extern ISRStub

FreeInterrupt0:
    cli
    push 0
    push 41
    jmp ISRStub