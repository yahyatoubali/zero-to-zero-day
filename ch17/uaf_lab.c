// uaf_lab.c — Use-After-Free with function pointer
// Compile: gcc -o uaf_lab uaf_lab.c -no-pie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void win(void) {
    printf("You hijacked control flow!\n");
}

void print_hello(char *name) {
    printf("Hello, %s!\n", name);
}

struct object {
    void (*func)(char *);
    char name[24];
};

int main(void) {
    struct object *obj = malloc(sizeof(struct object));
    obj->func = print_hello;
    strcpy(obj->name, "world");

    free(obj);  // Free the object

    // Attacker reallocates and overwrites
    struct object *attacker = malloc(sizeof(struct object));
    attacker->func = win;  // Overwrite function pointer

    obj->func("world");  // USE-AFTER-FREE
    return 0;
}
