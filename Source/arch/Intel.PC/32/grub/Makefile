ifneq ($(shell which grub-mkrescue),)
$(info Detected grub-mkrescue. Adding grub option)
genconfig:
	mkdir -p cd/boot/grub
	mkdir -p cd/kernel
	printf "menuentry \"kernel\" {\n" >> cd/boot/grub/grub.cfg
	printf "\techo Loading kernel...\n" >> cd/boot/grub/grub.cfg
	printf "\tmultiboot (cd)/kernel/$(OUTPUT)\n" >> cd/boot/grub/grub.cfg
	printf "\techo Booting kernel...\n" >> cd/boot/grub/grub.cfg
	printf "}\n" >> cd/boot/grub/grub.cfg
grub: genconfig
	cp $(OUTPUT) cd/kernel/$(OUTPUT)
	grub-mkrescue -o Result.iso cd
endif