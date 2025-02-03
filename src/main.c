#include "server.h"
// #include "request.h"
#include "response.h"
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
            // HttpRequest request;
            // parse_request(client_fd, &request);
            //
            // printf("Method: %s, Path: %s\n", request.method, request.path);
            // for (int i = 0; i < request.header_count; i++) {
            //     printf("Header: %s\n", request.headers[i]);
            // }

            send_response(client_fd, 200, "<h1>Hello, World!</h1>", "text/html");

            // Por agora, apenas fechar a conexão
            close(client_fd);
        }
    }

    return 0;
}
