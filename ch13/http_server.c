/*
 * Simple HTTP server with intentional buffer overflow.
 * For static analysis lab only.
 * Compile: gcc -o http_server http_server.c -no-pie -fno-stack-protector
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 256
#define PORT 8080

void handle_request(int client) {
    char buffer[64];
    char response[256];

    recv(client, buffer, sizeof(buffer), 0);

    // VULNERABILITY: sprintf without size limit
    sprintf(response, "GET /%s HTTP", buffer);
    send(client, response, strlen(response), 0);
    close(client);
}

int main(void) {
    int server_fd, client;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 3);

    printf("HTTP server on port %d\n", PORT);
    while (1) {
        client = accept(server_fd, NULL, NULL);
        handle_request(client);
    }
    return 0;
}
