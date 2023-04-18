
bits 32                         ; Директива nasm - 32 бит

section .text                   ; multiboot specification (первые 8 килобайт)
    align 4
    dd 0x1BADB002               ; магические цифры для индентификации ядра multiboot
    dd 0x00                     ; флаги
    dd - (0x1BADB002 + 0x00)    ; checksum
    
global start
extern kmain                    ; функция из main.c

start:
    cli                         ; отключить прерывания
    mov esp, stack_space        ; указатель стека
    call kmain                  ; вызвать cmain
    hlt                         ; остановить cpu

section .bss
resb 8192                       ; резервировать 8 килобайт
stack_space: