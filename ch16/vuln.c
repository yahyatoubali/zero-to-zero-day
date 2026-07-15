// vuln.c — Buffer overflow for ret2shellcode lab
// Compile: gcc -fno-stack-protector -no-pie -z execstack -o vuln vuln.c
#include <string.h>
#include <stdio.h>

void vulnerable(char *input) {
    char buffer[64];
    strcpy(buffer, input);
}

int main(int argc, char **argv) {
    vulnerable(argv[1]);
    return 0;
}
