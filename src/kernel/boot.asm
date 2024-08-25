
bits 32                         ; nasm - 32 bits

section .text                   ; multiboot specification (first 8 Kb)
    align 4
    dd 0x1BADB002               ; magic numbers for multiboot kernel identification
    dd 0x00                     ; flags
    dd - (0x1BADB002 + 0x00)    ; checksum

global start
extern kmain                    ; main function

start:
    cli                         ; interrupt
    mov esp, stack_space        ; stack pointer
    call kmain                  ;
    hlt                         ; cpu standstill

section .bss
resb 8192                       ; reserve 8 Kb

stack_space: