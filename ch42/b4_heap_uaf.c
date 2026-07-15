// B-4: Heap UAF Exploitation
// Compile: gcc -no-pie -o b4_uaf b4_uaf.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void win(void) {
    printf("You hijacked control flow!\n");
}

struct object {
    void (*func)(char *);
    char name[24];
};

int main(void) {
    struct object *obj = malloc(sizeof(struct object));
    obj->func = NULL;

    free(obj);  // Free the object

    // Attacker reallocates and overwrites
    struct object *attacker = malloc(sizeof(struct object));
    attacker->func = win;

    if (obj->func)
        obj->func("");  // USE-AFTER-FREE

    return 0;
}
