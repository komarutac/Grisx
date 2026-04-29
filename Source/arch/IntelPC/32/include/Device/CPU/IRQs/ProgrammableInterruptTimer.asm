global ProgrammableInterruptTimerInterrupt
extern ISRStub

ProgrammableInterruptTimerInterrupt:
    cli
    push 0
    push 32
    jmp ISRStub