// fastbin_dup.c — Fastbin double-free demonstration
// Compile: gcc -o fastbin_dup fastbin_dup.c -no-pie
//
// First fills the tcache bin for 0x50 size, then performs a fastbin dup:
// free(A), free(B), free(A) -> tcache is full, so frees go to fastbin.
// The fastbin only checks that top != chunk, so A->B->A passes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Fill the tcache bin for 0x50 size (7 entries)
    void *fill[7];
    for (int i = 0; i < 7; i++)
        fill[i] = malloc(0x48);
    for (int i = 0; i < 7; i++)
        free(fill[i]);   // tcache now full for this size

    // Fastbin dup: A, B, A
    void *a = malloc(0x48);
    void *b = malloc(0x48);
    void *c = malloc(0x48);

    printf("a = %p, b = %p, c = %p\n", a, b, c);

    free(a);
    free(b);
    free(a);   // Double-free! Fastbin: A -> B -> A -> B -> ...

    // Allocate twice -> both return A
    void *x = malloc(0x48);
    void *y = malloc(0x48);

    printf("x = %p, y = %p\n", x, y);

    if (x == a && y == a)
        printf("Fastbin dup successful! Overlapping allocations.\n");

    // Now both x and y point to A.
    // Any data written through y can be read through x.
    // In a real exploit: overwrite a function pointer through y.

    return 0;
}
