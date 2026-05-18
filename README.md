# Supported Platforms
1. IntelPC, 32
# Supported Loaders
1. Multiboot (IntelPC, 32)
# Tools Not Tested
Not tested with masm, gas, or fasm as the assembler.

Not tested with pcc, clang, or msvc as the compiler.
# Platform IntelPC, 32
## Build Requirements
1. gmake (bsdmake not support yet)
2. i386-elf-gcc or i686-elf-gcc
3. nasm or yasm
## Minimum System Requirements
1. CPU: 486
2. Memory: 2 MB
3. Video: EGA (Text Mode)
4. Machine: PCI
# Build
The compiled binary will be placed in the root of the Source folder (Source/Platform-Bits_Edition.elf).
```sh
gmake PROFILE=Profile AS=Assembler CC=CCompiler all
```
# Credits
Parts of the directory structure and files are from https://gitlab.com/sortie/meaty-skeleton
