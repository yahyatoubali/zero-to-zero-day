// fmt.c — Format string vulnerability
// Compile: gcc -o fmt fmt.c -no-pie
#include <stdio.h>

void vuln(void) {
    char buf[256];
    fgets(buf, 256, stdin);
    printf(buf);  // Format string vulnerability!
    printf("\n");
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    while (1) vuln();
    return 0;
}
