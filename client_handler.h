#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

typedef struct {
    int client_fd;
    int verbose;
} thread_args_t;

void *handle_client(void *arg);

#endif
