#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "http_request.h"
#include "util.h"
#include "HashTable_on_C/HashTable.h"
#include "http_response.h"


void printString(char *str){
    int countElements = strlen(str);
    for (int i = 0; i <= countElements; i++)
    {
        printf("%c", str[i]);
    }
    
}

HttpRequest* http_request_create(){

    HttpRequest *request = (HttpRequest*)malloc(sizeof(HttpRequest));

    request->method = NULL;
    request->path = NULL;
    request->protocol = NULL;
    request->version_protocol = NULL;
    request->headers = (char**)malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; i++)
    {
        request->headers[i] = (char*)malloc(10 * sizeof(char));
    }

    request->body = (char**)malloc(10 * sizeof(char*));
    for (int i = 0; i < 10; i++)
    {
        request->body[i] = (char*)malloc(10 * sizeof(char));
    }

    return request;
}


HttpRequest http_request_parse(char* rawHttpRequest){

    HttpRequest *http_request = http_request_create();

    int request_lines_count;
    char** request_lines = string_split(rawHttpRequest, '\n', &request_lines_count);

    char** request_parts_first_string = string_split(request_lines[0],' ', NULL);

    char** request_parts_protocol;

    http_request->method = request_parts_first_string[0];
    printf("%s\n",http_request->method);

    http_request->path = request_parts_first_string[1];
    printf("%s\n",http_request->path);

    request_parts_protocol = string_split(request_parts_first_string[2], '/', NULL);

    http_request->protocol = request_parts_protocol[0];
    printf("%s\n",http_request->protocol);

    http_request->version_protocol = request_parts_protocol[1];
    printf("%s\n",http_request->version_protocol);

    //----------------------------------------------------------------------;

    THashTable *hashTableForHaeders = hashTable_create();

    for (int i = 1; i < request_lines_count; i++)
    {
        int splittedHeaderCount;
        char** splitted_header = string_split(request_lines[i], ':', &splittedHeaderCount);

        char *header_data = "";

        for (int j = 1; j <= splittedHeaderCount; j++)
        {
            header_data = string_concat(header_data, splitted_header[j]);
        }

        hashTable_addItem(hashTableForHaeders, splitted_header[0], header_data);

    }
    hashTable_print(hashTableForHaeders);

}  

HttpResponse* http_response_create(){

    HttpResponse *response = (HttpResponse*)malloc(sizeof(HttpResponse));

    response->request_line = "HTTP/1.1 200 OK";
    response->header_fields = hashTable_create();
    response->body_Json = hashTable_create();

    hashTable_addItem(response->header_fields, "Content-Type" , "application/json");
    hashTable_addItem(response->header_fields, "Connection" , "keep-alive");
    hashTable_addItem(response->header_fields, "Content-Language" , "en-US");
    hashTable_addItem(response->header_fields, "Server" , "localhost");

    hashTable_print(response->header_fields);

    hashTable_addItem(response->body_Json, "{ body" , "/home/alex/Документы/Socket_2/server_reply.json }");
    hashTable_print(response->body_Json);

    return response;
}

int main()
{
    

    setvbuf(stdout, NULL, _IONBF, 0);
    //char server_message[256] = "You have reached the server!";
    char *server_message;
    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // BIND(СВЯЗЬ) the socket to our specified IP and port
    bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));
    
    // second argument is a backlog - how many connection can be 
    // waiting for this socket simultaneously(Одновременно)
    listen(server_socket, 5);
    
    int client_socket;
    
    client_socket = accept(server_socket, NULL, NULL);

    if( client_socket <= 0)
	{
		puts("accepted_file_type failed");
        return 1;
	}
    
    //receive data from the server
    char request[256];


    if( recv(client_socket, &request, sizeof(request), 0) < 0)
	{
		puts("recv failed");
	}
    else
    {
        printf("The client sent the data:%s\n", request);
    }
    
    http_request_parse(request);
    server_message = (char*)http_response_create();


    // send the message

    send(client_socket, server_message, sizeof(server_message), 0);    
    
    // close the socket
    close(server_socket);

    return 0;

}
