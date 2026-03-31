global CMOSRTCInterrupt
extern ISRStub

CMOSRTCInterrupt:
    cli
    push 0
    push 40
    jmp ISRStub