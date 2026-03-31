global VirtualizationException
extern ISRStub

VirtualizationException:
    cli
    push 0
    push 20
    jmp ISRStub