#include "request.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

void parse_request(int client_fd, HttpRequest *request) {
    char buffer[1024];

    int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);  
    if (bytes_read <= 0) {
        printf("Failed to read request\n");
        return;
    }

    buffer[bytes_read] = '\0';

    char *line = strtok(buffer, "\r\n");

    sscanf(line, "%s %s", request->method, request->path);

    request->header_count = 0;
    while ((line = strtok(NULL, "\r\n")) && request->header_count < MAX_HEADERS) {
        if (strlen(line) == 0) break;
        strcpy(request->headers[request->header_count], line);
        request->header_count++;
    }
}

