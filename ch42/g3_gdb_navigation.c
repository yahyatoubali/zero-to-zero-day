// G-3: GDB Navigation
// Compile: gcc -g -o g3_gdb g3_gdb.c
#include <stdio.h>

void secret_function(void) {
    printf("You found the secret!\n");
}

int main(void) {
    int local = 42;
    printf("local = %d\n", local);
    secret_function();
    return 0;
}
