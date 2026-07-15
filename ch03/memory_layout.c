#include <stdio.h>
#include <stdlib.h>

int global_var = 42;
static int static_var = 0;

int main(void) {
    int local_var = 10;
    int *heap_var = malloc(sizeof(int));
    *heap_var = 20;

    printf("Code (main):   %p\n", main);
    printf("Global (data): %p\n", &global_var);
    printf("Static (BSS):  %p\n", &static_var);
    printf("Local (stack): %p\n", &local_var);
    printf("Heap:          %p\n", heap_var);

    free(heap_var);
    return 0;
}
