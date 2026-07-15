// tcache_lab.c — Tcache poisoning lab
// Compile: gcc -no-pie -o tcache_lab tcache_lab.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char *chunks[16];
int idx = 0;

void win(void) {
    system("cat /etc/passwd");
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    char input[64];
    while (1) {
        printf("1. alloc 2. free 3. edit 4. exit\n> ");
        fgets(input, 64, stdin);
        switch (input[0]) {
            case '1':
                chunks[idx] = malloc(0x48);
                printf("chunk[%d] = %p\n", idx, chunks[idx]);
                idx++;
                break;
            case '2': {
                int i;
                scanf("%d", &i);
                free(chunks[i]);   // No NULL-after-free! UAF!
                break;
            }
            case '3': {
                int i;
                scanf("%d", &i);
                read(0, chunks[i], 0x48);  // Write to freed chunk
                break;
            }
            case '4': return 0;
        }
    }
}
