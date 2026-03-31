global FreeInterrupt1
extern ISRStub

FreeInterrupt1:
    cli
    push 0
    push 42
    jmp ISRStub