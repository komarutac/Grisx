global NonMaskableInterruptException
extern ISRStub

NonMaskableInterruptException:
    cli
    push 0
    push 2
    jmp ISRStub