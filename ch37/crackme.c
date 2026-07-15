// crackme.c — Simple crackme for angr symbolic execution
// Compile: gcc -o crackme crackme.c
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    char *input = argv[1];

    if (strlen(input) != 6) {
        puts("Wrong length");
        return 1;
    }

    if (input[0] + input[1] != 200) return 1;
    if (input[2] * input[3] != 22500) return 1;
    if (input[4] - input[5] != 10) return 1;
    if (input[0] != 'S') return 1;

    puts("Correct!");
    return 0;
}
