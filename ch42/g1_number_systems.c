// G-1: Number Systems Mastery
#include <stdio.h>
#include <limits.h>

int main(void) {
    // 1. Convert to binary and hex: 127, 255, 4096, 65537
    int nums[] = {127, 255, 4096, 65537};
    for (int i = 0; i < 4; i++) {
        printf("%d = 0x%x = 0b", nums[i], nums[i]);
        for (int b = 31; b >= 0; b--)
            putchar((nums[i] >> b) & 1 ? '1' : '0');
        putchar('\n');
    }

    // 3. Largest positive signed 32-bit integer
    printf("INT_MAX: %d (0x%x)\n", INT_MAX, INT_MAX);
    printf("INT_MIN: %d (0x%x)\n", INT_MIN, INT_MIN);

    // 4. Integer overflow demo
    unsigned char c = 255;
    printf("unsigned char 255 + 1 = %u (overflow!)\n", c + 1);

    // 5. "Hello" in hex (little-endian)
    char *hello = "Hello";
    printf("\"Hello\" hex: ");
    for (int i = 0; i < 5; i++)
        printf("%02x ", (unsigned char)hello[i]);
    printf("\n");

    return 0;
}
