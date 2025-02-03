#ifndef RESPONSE_H
#define RESPONSE_H

#include "request.h"

void handle_request(int client_fd, HttpRequest *request);
void send_response(int client_fd, int status_code, const char *body,
                   const char *content_type);

#endif
