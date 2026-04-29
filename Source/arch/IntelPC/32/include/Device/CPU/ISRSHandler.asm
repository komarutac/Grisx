;http://www.osdever.net/bkerndev/Docs/isrs.htm

global SystemCall
extern ISRStub

SystemCall:
    cli
    push 128
    jmp ISRStub