# Making a binary file which contains both the boot sector and the kernel itself
MyOS.bin: ./boot/boot.bin ./kernel/kernel.bin
	cat $< ./kernel/kernel.bin > $@


# Generating a 1.44MB floppy imgae that is zero filled
MyOS.img: MyOS.bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$< of=$@ conv=notrunc
# Finally copying the binary file into the floppy image without trunction

