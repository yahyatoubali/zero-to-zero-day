#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *a = malloc(32);
    char *b = malloc(32);
    char *c = malloc(32);

    strcpy(a, "Hello heap");
    printf("a: %s at %p\n", a, a);
    printf("b: at %p\n", b);
    printf("c: at %p\n", c);

    free(a);
    free(b);
    free(c);
    return 0;
}
