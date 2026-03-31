global CascadeInterrupt
extern ISRStub

CascadeInterrupt:
    cli
    push 0
    push 34
    jmp ISRStub