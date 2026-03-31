global CoprocessorSegmentOverrunException
extern ISRStub

CoprocessorSegmentOverrunException:
    cli
    push 0
    push 9
    jmp ISRStub