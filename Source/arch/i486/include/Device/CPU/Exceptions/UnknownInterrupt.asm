global UnknownInterruptException
extern ISRStub

UnknownInterruptException:
    cli
    push 0
    push 15
    jmp ISRStub