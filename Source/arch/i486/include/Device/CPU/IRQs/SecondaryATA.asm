global SecondaryATAInterrupt
extern ISRStub

SecondaryATAInterrupt:
    cli
    push 0
    push 47
    jmp ISRStub