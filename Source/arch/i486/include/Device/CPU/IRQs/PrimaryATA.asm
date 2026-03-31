global PrimaryATAInterrupt
extern ISRStub

PrimaryATAInterrupt:
    cli
    push 0
    push 46
    jmp ISRStub