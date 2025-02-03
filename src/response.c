#include "response.h"
#include "file_handler.h"
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
        strncpy(status_line, "HTTP/1.1 200 OK\r\n", sizeof(status_line) - 1);
    } else {
        strncpy(status_line, "HTTP/1.1 404 Not Found\r\n",
                sizeof(status_line) - 1);
    }

    status_line[sizeof(status_line) - 1] = '\0';

    int bytes_written =
        snprintf(response, sizeof(response),
                 "%sContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s",
                 status_line, content_type, strlen(body), body);

    if (bytes_written < 0 || bytes_written >= (int)sizeof(response)) {
        printf("ERROR: Response buffer overflow detected! (%d bytes needed)\n",
               bytes_written);
        return;
    }

    send(client_fd, response, bytes_written, 0);
}

void handle_request(int client_fd, HttpRequest *request) {
    char filepath[256] = "static";

    if (strncmp(request->path, "/static/", 8) == 0) {
        strcat(filepath, request->path + 7);
    } else {
        strcat(filepath, request->path);
    }

    printf("Processed filepath: %s\n", filepath);

    if (strcmp(request->method, "POST") == 0) {
        if (write_file(filepath, request->body)) {
            send_response(client_fd, 201, "<h1>Resource Created</h1>",
                          "text/html");
        } else {
            send_response(client_fd, 500, "<h1>Internal Server Error</h1>",
                          "text/html");
        }
    } else if (strcmp(request->method, "PUT") == 0) {
        if (write_file(filepath, request->body)) {
            send_response(client_fd, 200, "<h1>Resource Updated</h1>",
                          "text/html");
        } else {
            send_response(client_fd, 500, "<h1>Internal Server Error</h1>",
                          "text/html");
        }
    } else if (strcmp(request->method, "DELETE") == 0) {
        if (delete_file(filepath)) {
            send_response(client_fd, 200, "<h1>Resource Deleted</h1>",
                          "text/html");
        } else {
            send_response(client_fd, 404, "<h1>File Not Found</h1>",
                          "text/html");
        }
    } else {
        send_response(client_fd, 405, "<h1>Method Not Allowed</h1>",
                      "text/html");
    }
}
