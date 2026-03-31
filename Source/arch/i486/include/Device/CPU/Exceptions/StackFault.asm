global StackFaultException
extern ISRStub

StackFaultException:
    cli
    push 12
    jmp ISRStub