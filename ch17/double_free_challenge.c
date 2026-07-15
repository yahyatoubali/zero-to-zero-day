// double_free_challenge.c — Double Free bug
// Compile: gcc -o double_free double_free_challenge.c -no-pie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void double_free_bug(void) {
    char *p = malloc(32);
    free(p);
    free(p);  // Double free!

    // tcache bin for size 32 now contains: p -> p -> (old next)
    char *a = malloc(32);  // returns p
    char *b = malloc(32);  // also returns p!

    printf("a = %p, b = %p\n", a, b);
    if (a == b) {
        printf("Double free successful! Overlapping allocations.\n");
    }
}

int main(void) {
    double_free_bug();
    return 0;
}
