#ifndef SERVER_H
#define SERVER_H

int create_server_socket();
void bind_socket(int server_fd);
void start_listening(int server_fd);
int accept_client(int server_fd);

#endif
