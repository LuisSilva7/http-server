#ifndef REQUEST_H
#define REQUEST_H

#define MAX_HEADERS 20
#define MAX_HEADER_LENGTH 256

typedef struct {
    char method[10];
    char path[256];
    char headers[MAX_HEADERS][MAX_HEADER_LENGTH];
    int header_count;
} HttpRequest;

void parse_request(int client_fd, HttpRequest *request);

#endif
