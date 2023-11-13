#include "HashTable_on_C/HashTable.h"

typedef struct HTTP_response HttpResponse;

struct HTTP_response
{
    char *request_line; // HTTP/0.9 200 OK
    THashTable *header_fields; // Content-Type : application/json // можнол через хеш таблицу
    THashTable *body_Json; // пока без понятия как реализовать
};