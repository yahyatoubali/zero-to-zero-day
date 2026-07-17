// house_of_spirit.c — House of Spirit challenge
// Compile: gcc -o house_of_spirit house_of_spirit.c -no-pie
//
// Vulnerable function: buffer overflow overwrites heap_ptr on stack.
// Exploit: craft a fake chunk in buf, make heap_ptr point to it,
// free(heap_ptr) puts fake chunk in tcache, malloc returns stack pointer.
// Write to that pointer to overwrite return address.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void win(void) {
    printf("You hijacked control flow!\n");
}

void vuln(void) {
    char buf[64];
    void *heap_ptr = malloc(0x48);
    printf("buf at %p, heap_ptr at %p\n", buf, &heap_ptr);

    printf("Enter data: ");
    fgets(buf, 128, stdin);  // Overflow! Can overwrite heap_ptr

    free(heap_ptr);              // Frees our fake chunk
    char *a = malloc(0x48);      // Returns fake chunk address
    read(0, a, 0x48);            // Write to stack
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    vuln();
    return 0;
}
