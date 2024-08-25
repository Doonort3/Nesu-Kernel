echo "Compile boot.asm... (nasm)"
nasm -f elf32 boot.asm -o boot.o
echo "Compile kernel.c and others... (gcc)"
gcc -m32 -c kernel.c -o kc.o
echo "Linking... (ld)"
ld -m elf_i386 -T link.ld -o rm_kernel boot.o kc.o
echo "Start qemu (i386)"
qemu-system-i386 -kernel rm_kernel