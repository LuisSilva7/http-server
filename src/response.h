#ifndef RESPONSE_H
#define RESPONSE_H

void send_response(int client_fd, int status_code, const char *body,
                   const char *content_type);

#endif
