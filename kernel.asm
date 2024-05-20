; src/kernel.asm

; Multiboot header
section .multiboot
    align 4
    dd 0x1BADB002              ; magic number
    dd 0x00                    ; flags
    dd - (0x1BADB002 + 0x00)   ; checksum

section .text
extern kernel_main

global _start
_start:
    cli                        ; Disable interrupts

    ; Set up the stack
    mov esp, stack_space + stack_size

    ; Call the C kernel main function
    call kernel_main

.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_space:
    resb 8192
stack_size equ $ - stack_space
