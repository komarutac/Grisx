global MachineCheckException
extern ISRStub

MachineCheckException:
    cli
    push 0
    push 18
    jmp ISRStub