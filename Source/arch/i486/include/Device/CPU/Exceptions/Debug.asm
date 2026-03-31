global DebugException
extern ISRStub

DebugException:
    cli
    push 0
    push 1
    jmp ISRStub