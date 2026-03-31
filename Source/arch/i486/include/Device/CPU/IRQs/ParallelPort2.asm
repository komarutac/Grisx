global LPT2Interrupt
extern ISRStub

LPT2Interrupt:
    cli
    push 0
    push 37
    jmp ISRStub