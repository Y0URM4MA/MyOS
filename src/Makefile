# Automatically  expand  to a list of  existing  files  that
# match  the  patterns
C_SOURCES = $(wildcard  kernel/*.c drivers/*.c)
HEADERS = $(wildcard  kernel/*.h drivers/*.h)

# Convert  the *.c filenames  to *.o to give a list of  object  files  to  build
OBJ = ${C_SOURCES:.c=.o}

# This  builds  the  binary  of our  kernel  from  two  object  files:
#   - the  kernel_entry , which  jumps  to main() in our  kernel
#   - the  compiled C kernel
kernel.bin: kernel/kernel_entry.o kernel/interrupt.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x7e00 $^ --oformat  binary

# Generic  rule  for  compiling C code to an  object  file
# For  simplicity , we C files  depend  on all  header  files.
%.o : %.c ${HEADERS}
	i386-elf-gcc -ffreestanding -I./headers -c $< -o $@

kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf -o $@

interrupt.o: kernel/interrupt.asm
	nasm $< -f elf -o kernel/$@
