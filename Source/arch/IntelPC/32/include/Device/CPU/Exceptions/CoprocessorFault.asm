global CoprocessorFaultException
extern ISRStub

CoprocessorFaultException:
    cli
    push 0
    push 16
    jmp ISRStub