// B-2: Return to libc (same binary, NX enabled)
// Compile: gcc -fno-stack-protector -no-pie -o b2_ret2libc b2_ret2libc.c
#include <stdio.h>
#include <string.h>

void vulnerable(char *input) {
    char buffer[64];
    strcpy(buffer, input);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    vulnerable(argv[1]);
    return 0;
}
