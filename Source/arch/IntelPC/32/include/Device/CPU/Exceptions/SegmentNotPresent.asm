global SegmentNotPresentException
extern ISRStub

SegmentNotPresentException:
    cli
    push 11
    jmp ISRStub