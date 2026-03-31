global GeneralProtectionFaultException
extern ISRStub

GeneralProtectionFaultException:
    cli
    push 13
    jmp ISRStub