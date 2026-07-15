#include <stdio.h>
#include <limits.h>

int main(void) {
    printf("Signed INT_MAX: %d (0x%x)\n", INT_MAX, INT_MAX);
    printf("Signed INT_MIN: %d (0x%x)\n", INT_MIN, INT_MIN);
    printf("Unsigned UINT_MAX: %u (0x%x)\n", UINT_MAX, UINT_MAX);

    // Integer overflow demonstration
    unsigned char c = 255;
    printf("unsigned char 255 + 1 = %u\n", c + 1);

    signed char s = 127;
    printf("signed char 127 + 1 = %d\n", s + 1);

    return 0;
}
