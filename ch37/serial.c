// serial.c — Serial number checker for symbolic execution
// Compile: gcc -o serial serial.c
#include <stdio.h>

int check(char *s) {
    int sum = 0;
    for (int i = 0; s[i]; i++) {
        sum += s[i] * (i + 1);
    }
    return sum == 0x539;  // 1337
}

int main(int argc, char **argv) {
    if (argc == 2 && check(argv[1])) {
        printf("Valid serial!\n");
    }
    return 0;
}
