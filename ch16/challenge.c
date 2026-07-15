// challenge.c — Canary + ASLR + Format String Leak lab
// Compile: gcc -o challenge challenge.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void vuln(void) {
    char buffer[64];
    char format[256];

    printf("Enter format: ");
    fgets(format, 256, stdin);
    printf(format);  // Format string vulnerability

    printf("Enter data: ");
    read(0, buffer, 200);  // Stack overflow
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    vuln();
    return 0;
}
