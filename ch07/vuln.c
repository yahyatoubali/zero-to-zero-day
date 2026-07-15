#include <stdio.h>
#include <string.h>

void vuln_function(char *input) {
    char buffer[64];
    strcpy(buffer, input);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    vuln_function(argv[1]);
    return 0;
}
