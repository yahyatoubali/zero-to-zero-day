// challenge.c — Integer underflow in packet parsing
// Compile: gcc -o challenge challenge.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    unsigned int len;
    char data[0];
} __attribute__((packed)) message;

message *parse_msg(unsigned int body_len, const char *body) {
    unsigned int total = body_len + sizeof(message);
    // If body_len is 0xFFFFFFFF, total = 0xFFFFFFFF + 8 = 7 (integer overflow!)
    message *msg = malloc(total);
    if (!msg) return NULL;
    msg->len = body_len;
    memcpy(msg->data, body, body_len);  // Heap overflow!
    return msg;
}

int main(void) {
    message *msg = parse_msg(0xFFFFFFFF, "AAAA");
    printf("msg->len = %u\n", msg->len);
    return 0;
}
