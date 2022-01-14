#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <signal.h>

#include "http.h"
#include "utils.h"
#include "tcp.h"

#define MAX_BUFFER 1024
#define PORT 8080

typedef int listener_t;
typedef int socket_t;

volatile sig_atomic_t done = 0;

void terminate_server(int signal) {
    printf("Stopping server...");
    done = 1;
}

char* create_response(char* request) {
    http_headers_t headers = calloc(MAX_BUFFER, sizeof(char));
    append(headers, "Content-Type", "text/html; charset=utf-8");
    if(starts_with(request, "GET / HTTP/1.1")) {
        http_response_t response = http_response("HTTP/1.1", 200, "OK", MAX_BUFFER);
        set_headers(response, headers);
        free(headers);
        set_body(response, "<h1>Hello World</h1>");
        return response;
    } else {
        http_response_t response = http_response("HTTP/1.1", 404, "Not Found", MAX_BUFFER);
        set_headers(response, headers);
        free(headers);
        set_body(response, "<h1>404: Not Found</h1>");
        return response;
    }
}

int main(int argc, char** argv) {
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = terminate_server;
    sigaction(SIGTERM, &action, NULL);

    listener_t server = listen_tcp(PORT);

    while(true) {
        if(done == 1) {
            err_t closed = close(server);
            handle_error(closed, "Failed to close port!");
            exit(0);
        }
        socket_t client = accept(server, NULL, NULL);

        char request_buffer[MAX_BUFFER];
        read(client, request_buffer, MAX_BUFFER);
        log_message(READ_MESSAGE, request_buffer);

        char* response = create_response(request_buffer);
        // send(client, response, strlen(response), 0);
        write(client, response, strlen(response));
        log_message(WRITE_MESSAGE, response);

        free(response);
        shutdown(client, SHUT_RDWR);
        close(client);
    }
}