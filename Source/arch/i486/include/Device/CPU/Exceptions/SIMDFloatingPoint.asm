global SIMDFloatingPointException
extern ISRStub

SIMDFloatingPointException:
    cli
    push 0
    push 19
    jmp ISRStub