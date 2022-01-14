#include <stdbool.h>

typedef int err_t;

#define READ_MESSAGE 0
#define WRITE_MESSAGE 1

void handle_error(err_t err, const char* message);

void log_message(int type, const char* message);

bool starts_with(char* string, char* starting);