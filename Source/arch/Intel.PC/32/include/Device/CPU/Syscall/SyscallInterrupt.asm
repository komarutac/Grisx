global SyscallInterrupt
extern SyscallStub

SyscallInterrupt:
    cli
    push 0
    push 128
    jmp SyscallStub