#include "client_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void *handle_client(void *arg) {
    thread_args_t *args = (thread_args_t *)arg;
    int client_fd       = args->client_fd;
    int verbose         = args->verbose;
    free(arg);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(client_fd, buffer, sizeof(buffer))) > 0) {
        if (verbose) {
            fwrite(buffer, 1, bytes_read, stdout);
            fflush(stdout);
        }
        write(client_fd, buffer, bytes_read);
    }

    close(client_fd);
    return NULL;
}
