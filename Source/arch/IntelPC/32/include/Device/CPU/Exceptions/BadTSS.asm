global BadTSSException
extern ISRStub

BadTSSException:
    cli
    push 10
    jmp ISRStub