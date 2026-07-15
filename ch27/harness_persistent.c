// harness_persistent.c — AFL++ persistent mode harness
// Compile: afl-clang-fast -o harness_persistent harness_persistent.c -lafl-driver
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int parse_data(const unsigned char *data, size_t len);

int main(int argc, char **argv) {
    unsigned char *buf = __AFL_FUZZ_INIT();

    while (__AFL_LOOP(10000)) {
        size_t len = read(0, buf, 65536);
        parse_data(buf, len);
    }

    return 0;
}

int parse_data(const unsigned char *data, size_t len) {
    if (len < 4) return -1;
    if (data[0] == 'A' && data[1] == 'B' && data[2] == 'C' && data[3] == 'D') {
        // Trigger a crash
        abort();
    }
    return 0;
}
