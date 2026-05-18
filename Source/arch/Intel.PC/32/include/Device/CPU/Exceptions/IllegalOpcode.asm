global InvalidOpcodeException
extern ISRStub

InvalidOpcodeException:
    cli
    push 0
    push 6
    jmp ISRStub