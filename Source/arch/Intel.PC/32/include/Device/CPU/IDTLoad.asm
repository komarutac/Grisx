;http://www.osdever.net/bkerndev/Docs/idt.htm
global IDTLoad
extern IDTP

IDTLoad:
    lidt [IDTP]
    ret