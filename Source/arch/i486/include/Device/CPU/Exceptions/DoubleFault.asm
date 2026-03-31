global DoubleFaultException
extern ISRStub

DoubleFaultException:
    cli
    push 8
    jmp ISRStub