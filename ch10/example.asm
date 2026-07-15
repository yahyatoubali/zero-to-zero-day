; x86-64 basic assembly examples
; Compile: nasm -f elf64 -o example.o example.asm && ld -o example example.o

section .data
    msg db "Hello, Assembly!", 0

section .text
    global _start

_start:
    ; write(1, msg, 17)
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel msg]
    mov rdx, 17
    syscall

    ; exit(0)
    mov rax, 60
    xor rdi, rdi
    syscall
