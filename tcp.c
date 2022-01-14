#include <sys/socket.h>
#include <netinet/in.h>

#include "utils.h"

int listen_tcp(int port) {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    err_t bound = bind(server, (struct sockaddr *) &address, sizeof(address));
    handle_error(bound, "Failed to bind socket to bound!");

    err_t listening = listen(server, 10);
    handle_error(listening, "Failed to start listening!");

    return server;
}