global UnitInterrupt
extern ISRStub

UnitInterrupt:
    cli
    push 0
    push 45
    jmp ISRStub