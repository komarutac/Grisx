global OutOfBoundsException
extern ISRStub

OutOfBoundsException:
    cli
    push 0
    push 5
    jmp ISRStub