global KeyboardInterrupt
extern ISRStub

KeyboardInterrupt:
    cli
    push 0
    push 33
    jmp ISRStub