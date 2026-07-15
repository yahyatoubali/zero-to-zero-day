// vulnerable.c — Vulnerable function for KLEE bug finding
// Compile: clang -emit-llvm -c -g vulnerable.c -o vulnerable.bc
#include <string.h>
#include <stdlib.h>

void vulnerable(char *input) {
    char buf[16];
    strcpy(buf, input);  // Buffer overflow if input > 15 chars
}
