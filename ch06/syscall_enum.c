#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(void) {
    printf("SYS_read:   %d\n", SYS_read);
    printf("SYS_write:  %d\n", SYS_write);
    printf("SYS_open:   %d\n", SYS_open);
    printf("SYS_close:  %d\n", SYS_close);
    printf("SYS_mmap:   %d\n", SYS_mmap);
    printf("SYS_execve: %d\n", SYS_execve);
    printf("SYS_clone:  %d\n", SYS_clone);
    return 0;
}
