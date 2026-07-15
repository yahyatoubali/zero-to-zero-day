// vuln.c — Integer overflow leading to heap overflow
// Compile: gcc -o vuln vuln.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    unsigned short count;
    unsigned short size;
    char *data;
} packet;

packet *parse_packet(unsigned short count, unsigned short size) {
    packet *p = malloc(sizeof(packet));
    if (!p) return NULL;
    p->count = count;
    p->size = size;
    // Integer overflow: count * size wraps with unsigned short!
    p->data = malloc(count * size);
    if (!p->data) { free(p); return NULL; }
    return p;
}

int main(void) {
    // 656 * 100 = 65600, truncated to unsigned short: 65600 - 65536 = 64
    packet *p = parse_packet(656, 100);
    printf("Allocated %hu bytes for %hu * %hu\n",
           p->count * p->size, p->count, p->size);
    // Writes 65600 bytes into a 64-byte buffer -> overflow
    return 0;
}
