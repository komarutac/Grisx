global BreakpointException
extern ISRStub

BreakpointException:
    cli
    push 0
    push 3
    jmp ISRStub