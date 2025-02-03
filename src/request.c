#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void parse_request(int client_fd, HttpRequest *request) {
    char buffer[4096];
    int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_read <= 0) {
        printf("Failed to read request\n");
        return;
    }

    buffer[bytes_read] = '\0';

    char *body_start = strstr(buffer, "\r\n\r\n");
    if (body_start) {
        *body_start = '\0';
        body_start += 4;
    } else {
        body_start = "";
    }

    char *line = strtok(buffer, "\r\n");
    if (!line) {
        printf("Invalid request format\n");
        return;
    }

    char method[10] = {0}, path[512] = {0};
    sscanf(line, "%9s %511s", method, path);

    strncpy(request->method, method, sizeof(request->method) - 1);
    request->method[sizeof(request->method) - 1] = '\0';

    strncpy(request->path, path, sizeof(request->path) - 1);
    request->path[sizeof(request->path) - 1] = '\0';

    request->header_count = 0;
    int content_length = 0;

    char *header_line;
    while ((header_line = strtok(NULL, "\r\n")) &&
           request->header_count < MAX_HEADERS) {
        if (!header_line)
            break;

        if (strlen(header_line) == 0)
            break;

        if (strncmp(header_line, "Content-Length:", 15) == 0) {
            content_length = atoi(header_line + 15);
        }

        strncpy(request->headers[request->header_count], header_line,
                MAX_HEADER_LENGTH - 1);
        request->headers[request->header_count][MAX_HEADER_LENGTH - 1] = '\0';
        request->header_count++;
    }

    if (content_length > 0 && body_start) {
        int copy_size = content_length < MAX_BODY_SIZE - 1 ? content_length
                                                           : MAX_BODY_SIZE - 1;
        strncpy(request->body, body_start, copy_size);
        request->body[copy_size] = '\0';
    } else {
        request->body[0] = '\0';
    }

    printf("Extracted body: %s\n", request->body);
}

void print_request_debug(HttpRequest *request) {
    printf("=== DEBUG: HttpRequest ===\n");
    printf("Method: %s\n", request->method);
    printf("Path: %s\n", request->path);
    printf("Headers (%d):\n", request->header_count);
    for (int i = 0; i < request->header_count; i++) {
        printf("  %s\n", request->headers[i]);
    }
    printf("Body (%lu bytes): %s\n", strlen(request->body), request->body);
    printf("===========================\n");
}
