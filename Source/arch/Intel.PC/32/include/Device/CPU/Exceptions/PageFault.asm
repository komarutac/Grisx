global PageFaultException
extern ISRStub

PageFaultException:
    cli
    push 14
    jmp ISRStub