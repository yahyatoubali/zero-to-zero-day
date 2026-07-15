// B-1: Classic Stack Smashing
// Compile: gcc -fno-stack-protector -no-pie -z execstack -o b1_stack b1_stack.c
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
