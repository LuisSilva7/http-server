#include "response.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

void send_response(int client_fd, int status_code, const char *body,
                   const char *content_type) {
    char response[2048];
    char status_line[32];

    if (status_code == 200) {
        strcpy(status_line, "HTTP/1.1 200 OK\r\n");
    } else {
        strcpy(status_line, "HTTP/1.1 404 Not Found\r\n");
    }

    snprintf(response, sizeof(response),
             "%sContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s", status_line,
             content_type, strlen(body), body);

    send(client_fd, response, strlen(response), 0);
}
