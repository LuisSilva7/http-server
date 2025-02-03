#include "response.h"
#include "request.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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

void handle_request(int client_fd, HttpRequest *request) {
    if (strcmp(request->path, "/") == 0) {
        send_response(client_fd, 200, "<h1>Welcome to the Homepage!</h1>",
                      "text/html");
    } else if (strcmp(request->path, "/about") == 0) {
        send_response(client_fd, 200,
                      "<h1>About Us</h1><p>We are a simple HTTP server.</p>",
                      "text/html");
    } else {
        send_response(client_fd, 404,
                      "<h1>Not Found</h1><p>Please comeback later.</p>",
                      "text/html");
    }
}
