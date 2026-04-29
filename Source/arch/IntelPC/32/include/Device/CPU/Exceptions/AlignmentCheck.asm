global AlignmentCheckException
extern ISRStub

AlignmentCheckException:
    cli
    push 0
    push 17
    jmp ISRStub