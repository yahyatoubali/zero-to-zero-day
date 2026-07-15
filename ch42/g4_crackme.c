// G-4: Crackme Challenge (password: "secret")
// Compile: gcc -o g4_crackme g4_crackme.c
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "secret") == 0) {
        printf("Correct!\n");
    } else {
        printf("Wrong password.\n");
    }

    return 0;
}
