global FloppyDiskInterrupt
extern ISRStub

FloppyDiskInterrupt:
    cli
    push 0
    push 38
    jmp ISRStub