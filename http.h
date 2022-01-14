
typedef char* http_response_t;
typedef char* http_headers_t;
typedef char* http_body_t;

void append(http_headers_t headers, char* key, char* value);

http_response_t http_response(char* version, int code, char* status, size_t size);

void set_headers(http_response_t response, http_headers_t headers);

void set_body(http_response_t response, http_body_t body);