#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define READ_MESSAGE 0
#define WRITE_MESSAGE 1

typedef int err_t;

void handle_error(err_t err, const char* message) {
    if(err != 0) {
        printf("%s\n", message);
        printf("%s\n", strerror(errno));
    }
}

void log_message(int type, const char* message) {
    if(type == READ_MESSAGE) {
        printf("Received %lu bytes: %s", strlen(message), message);
    } else if(type == WRITE_MESSAGE) {
        printf("Sent %lu bytes: %s", strlen(message), message);
    }
    printf("\n");
}

bool starts_with(char* string, char* starting) {
    size_t lenpre = strlen(starting),
            lenstr = strlen(starting);
    return lenstr < lenpre ? false : strncmp(starting, string, lenpre) == 0;
}