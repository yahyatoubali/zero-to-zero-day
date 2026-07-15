// B-5: Fuzzing Lab harness
// Compile with AFL++: afl-gcc -o b5_fuzz b5_fuzz.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_data(const unsigned char *data, size_t len) {
    if (len < 4) return -1;

    // Intentionally vulnerable parser
    if (data[0] == 'A' && data[1] == 'B') {
        if (data[2] == 'C' && data[3] == 'D') {
            // Trigger crash on specific input
            volatile int *p = NULL;
            *p = 0;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);
    unsigned char *buf = malloc(len + 1);
    fread(buf, 1, len, f);
    buf[len] = 0;
    fclose(f);
    parse_data(buf, len);
    free(buf);
    return 0;
}
