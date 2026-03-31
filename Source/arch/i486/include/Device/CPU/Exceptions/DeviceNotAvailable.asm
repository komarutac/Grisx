global DeviceNotAvailableException
extern ISRStub

DeviceNotAvailableException:
    cli
    push 0
    push 7
    jmp ISRStub