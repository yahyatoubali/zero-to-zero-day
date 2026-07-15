#include <stdio.h>

void stack_frame(void) {
    char buffer[64];
    sprintf(buffer, "Stack frame demo");
}

int main(void) {
    int local = 42;
    printf("local at: %p\n", &local);
    stack_frame();
    return 0;
}
