global LPT1Interrupt
extern ISRStub

LPT1Interrupt:
    cli
    push 0
    push 39
    jmp ISRStub