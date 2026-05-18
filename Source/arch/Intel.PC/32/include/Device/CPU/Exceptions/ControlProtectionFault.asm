global ControlProtectionFault
extern ISRStub

ControlProtectionFault:
    cli
    push 21
    jmp ISRStub