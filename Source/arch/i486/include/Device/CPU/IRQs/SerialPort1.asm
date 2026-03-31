global COM1Interrupt
extern ISRStub

COM1Interrupt:
    cli
    push 0
    push 36
    jmp ISRStub