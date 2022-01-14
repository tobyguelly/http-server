#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef char* http_response_t;
typedef char* http_headers_t;
typedef char* http_body_t;

void append(http_headers_t headers, char* key, char* value) {
    strcat(headers, key);
    strcat(headers, ": ");
    strcat(headers, value);
    strcat(headers, "\r\n");
}

http_response_t http_response(char* version, int code, char* status, size_t size) {
    http_response_t response = calloc(size, sizeof(char));
    sprintf(response, "%s %d %s\r\n", version, code, status);
    return response;
}

void set_headers(http_response_t response, http_headers_t headers) {
    strcat(response, headers);
}

void set_body(http_response_t response, http_body_t body) {
    strcat(response, "\r\n");
    strcat(response, body);
}