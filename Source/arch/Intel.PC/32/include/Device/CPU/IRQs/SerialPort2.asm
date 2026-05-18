global COM2Interrupt
extern ISRStub

COM2Interrupt:
    cli
    push 0
    push 35
    jmp ISRStub