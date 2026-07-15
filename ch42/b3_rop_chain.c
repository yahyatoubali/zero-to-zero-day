// B-3: ROP Chain Construction
// Compile: gcc -fno-stack-protector -no-pie -o b3_rop b3_rop.c
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
