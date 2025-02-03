#include "server.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    int server_fd = create_server_socket();
    bind_socket(server_fd);
    start_listening(server_fd);

    printf("Server is running on port 8080...\n");

    while (1) {
        accept_client(server_fd);
    }

    return 0;
}
