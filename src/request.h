#ifndef REQUEST_H
#define REQUEST_H

#define MAX_HEADERS 20
#define MAX_HEADER_LENGTH 256
#define MAX_BODY_SIZE 4096

typedef struct {
    char method[10];
    char path[256];
    char headers[MAX_HEADERS][MAX_HEADER_LENGTH];
    int header_count;
    char body[MAX_BODY_SIZE];
} HttpRequest;

void parse_request(int client_fd, HttpRequest *request);
void print_request_debug(HttpRequest *request);

#endif
