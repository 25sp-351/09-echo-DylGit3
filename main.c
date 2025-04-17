#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

int main(int argc, char *argv[]) {
    int port    = 2345;
    int verbose = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-p") && i + 1 < argc) {
            port = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "-v")) {
            verbose = 1;
        } else {
            fprintf(stderr, "Usage: %s [-p port] [-v]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    start_server(port, verbose);
    return 0;
}
