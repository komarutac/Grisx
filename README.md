# Build Requirements
1. make
2. i686-elf-gcc
3. nasm
# Supported Platform
1. IntelPC, 32
# Minimum System Requirements (IntelPC, 32)
1. CPU: 486
2. Memory: 2 MB
3. Video: EGA (Text Mode)
4. Machine: PCI
# Build (IntelPC, 32)
The compiled binary will be placed in the root of the Source folder.
```sh
make PLATFORM=IntelPC BITS=32 all
```