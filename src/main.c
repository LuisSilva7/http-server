#include "server.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    int server_fd = create_server_socket();
    bind_socket(server_fd);
    start_listening(server_fd);

    printf("Server is running on port 8080...\n");

    while (1) {
        int client_fd = accept_client(server_fd);
        if (client_fd >= 0) {
            // Por agora, apenas fechar a conexão
            close(client_fd);
        }
    }

    return 0;
}

