global OverflowException
extern ISRStub

OverflowException:
    cli
    push 0
    push 4
    jmp ISRStub