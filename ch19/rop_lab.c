// rop_lab.c — Two-stage ROP chain lab
// Compile: gcc -o rop_lab rop_lab.c -no-pie -fno-stack-protector
#include <stdio.h>
#include <unistd.h>

void vuln(void) {
    char buf[16];
    read(0, buf, 200);
}

int main(void) {
    vuln();
    return 0;
}
