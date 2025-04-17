#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "client_handler.h"

void start_server(int port, int verbose) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family         = AF_INET;
    server_addr.sin_port           = htons(port);
    server_addr.sin_addr.s_addr    = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int *client_fd     = malloc(sizeof(int));
        if (!client_fd) {
            perror("malloc");
            continue;
        }

        *client_fd =
            accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (*client_fd < 0) {
            perror("accept");
            free(client_fd);
            continue;
        }

        pthread_t tid;
        thread_args_t *args = malloc(sizeof(thread_args_t));
        if (!args) {
            perror("malloc");
            close(*client_fd);
            free(client_fd);
            continue;
        }

        args->client_fd = *client_fd;
        args->verbose   = verbose;
        free(client_fd);

        if (pthread_create(&tid, NULL, handle_client, args) != 0) {
            perror("pthread_create");
            close(args->client_fd);
            free(args);
        } else {
            pthread_detach(tid);
        }
    }

    close(server_fd);
}
