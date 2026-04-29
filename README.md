# Supported Platforms
1. IntelPC, 32
# Supported Loaders
1. Multiboot (IntelPC, 32)
# Platform IntelPC, 32
## Build Requirements
1. make
2. i686-elf-gcc
3. nasm
## Minimum System Requirements
1. CPU: 486
2. Memory: 2 MB
3. Video: EGA (Text Mode)
4. Machine: PCI
## Build
The compiled binary will be placed in the root of the Source folder.
```sh
make PLATFORM=IntelPC BITS=32 LOADER=Loader all
```