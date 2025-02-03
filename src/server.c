#include "server.h"
#include "request.h"
#include "response.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

int create_server_socket() {
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void bind_socket(int server_fd) {
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void start_listening(int server_fd) {
    int backlog = 5;

    if (listen(server_fd, backlog) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

void accept_client(int server_fd) {
    while (1) {
        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, NULL, NULL);
        if (*client_fd < 0) {
            perror("Accept failed");
            free(client_fd);
            continue;
        }

        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, client_fd) != 0) {
            perror("Failed to create thread");
            free(client_fd);
            continue;
        }

        pthread_detach(thread);
    }
}

void *handle_client(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);

    printf("Handling client in a new thread...\n");

    // ⚠️ Chamar aqui a função para processar o pedido e enviar a resposta
    HttpRequest request;
    parse_request(client_fd, &request);

    printf("Method: %s, Path: %s\n", request.method, request.path);
    for (int i = 0; i < request.header_count; i++) {
        printf("Header: %s\n", request.headers[i]);
    }

    handle_request(client_fd, &request);

    close(client_fd);
    return NULL;
}
