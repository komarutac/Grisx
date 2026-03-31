global MouseInterrupt
extern ISRStub

MouseInterrupt:
    cli
    push 0
    push 44
    jmp ISRStub