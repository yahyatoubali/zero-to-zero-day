// harness.c — AFL++ basic fuzzing harness
// Compile: afl-gcc -o harness harness.c -lafl-driver
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int parse_data(const unsigned char *data, size_t len);

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 1;

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    unsigned char *buf = malloc(len + 1);
    fread(buf, 1, len, f);
    buf[len] = 0;
    fclose(f);

    int result = parse_data(buf, len);

    free(buf);
    return 0;
}

// Dummy target function for testing
int parse_data(const unsigned char *data, size_t len) {
    if (len < 4) return -1;

    if (data[0] == 'A' && data[1] == 'B' && data[2] == 'C') {
        if (data[3] == 'D') {
            // Trigger crash on specific input
            char *p = NULL;
            *p = 0;
        }
    }
    return 0;
}
