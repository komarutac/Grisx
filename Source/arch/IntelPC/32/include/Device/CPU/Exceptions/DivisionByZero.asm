global DivisionByZeroException
extern ISRStub

DivisionByZeroException:
    cli
    push 0
    push 0
    jmp ISRStub