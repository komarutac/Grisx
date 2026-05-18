.set MultibootAlign, 1<<0
.set MultibootMemoryInfo, 1<<1
.set MultibootFlags, MultibootAlign | MultibootMemoryInfo
.set MultibootMagic, 0x1BADB002
.set MultibootChecksum, -(MultibootMagic + MultibootFlags)

.section .Multiboot
.align 4
.long MultibootMagic
.long MultibootFlags
.long MultibootChecksum

.section .bss
.align 16
StackBottom:
.skip 16384
StackTop:

.section .text
.global Start

Start:
	cli
    mov $StackTop, %esp
    push %ebx
    call GDTInstall
    call Loader