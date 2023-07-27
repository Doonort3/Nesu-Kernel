nasm -f elf32 boot.asm -o boot.o
gcc -m32 -c kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o rm_kernel boot.o kc.o
qemu-system-i386 -kernel rm_kernel