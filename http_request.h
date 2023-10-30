
typedef struct HTTP_request HttpRequest;

struct HTTP_request
{
    char* method;
    char* path;
    char* protocol;
    char* version_protocol;
    char** headers;
    char** body;
};

