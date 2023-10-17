#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "http_request.h"

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
    request->headers = NULL;
    request->body = NULL;

    return request;
}

char[10][10] string_split(char *inputString, char separator){

    char splittedString[10][10];
    char splittedPartString[10];
    int splittedStringIndex = 0;
    int splittedPartStringIndex = 0;
    for (int inputStringIndex = 0; inputStringIndex < strlen(inputString); inputStringIndex++)
    {
        
        splittedPartString[splittedPartStringIndex] = inputString[inputStringIndex];
    
        if (inputString[inputStringIndex] == separator)
        {
            splittedString[splittedStringIndex] = splittedPartString;
            splittedStringIndex++;
            for (int i = 0; i < 10; i++)
            {
                splittedPartString[i] = "\0";
            }
            splittedPartStringIndex = 0;
        }
        splittedPartStringIndex++;
    }

    return splittedString;
}

HttpRequest http_request_parse(char* rawHttpRequest){

    HttpRequest *http_request = http_request_create();

    char *our_request = rawHttpRequest;
    // 1) Сплит по /n
    // 2) ОБработка превой строки (разделить по пробелам)
    // 3) Сплит по : 

    //printf("%s", our_request);
    char *sep = "\n";
    char *string_message = strtok(our_request, sep);
    //printf("%s", string_message); 
    char *doubleString;
    //char *str;
    http_request->method = string_message;

    char separator = ' ';
    printf("%s\n", doubleString);
    char *str = string_split(http_request->method, separator);

    while (str == NULL)
    {
        str = string_split(doubleString, " ");
        printf("%s", str);

        if (http_request->method == NULL)
        {
            http_request->method = str;
        }
        else if (http_request->path == NULL)
        {
            http_request->path = str;
        }
        else if (http_request->protocol == NULL)
        {
            http_request->protocol = str;
        }
        else
        {
            http_request->version_protocol = str;
        }

    }
    printf("%s", http_request->method);
    printf("%s", http_request->path);
    printf("%s", http_request->protocol);
    printf("%s", http_request->version_protocol);
    
    //http_request->method = string_split(http_request->method, " ");

    //printf("%s\n", http_request->method);
    // while (string_message != NULL)
    // {
    //     // printf("%s\n", string_message);
    //     string_message = strtok(our_request,sep);
    //     str = string_message;
    //     printf("%s", string_message);
    // }
    //printf("%s", http_request->method);
}    

int main()
{
    char server_message[256] = "You have reached the server!";

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

    //split_on_C(request);

    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);    
    
    // close the socket
    close(server_socket);

    return 0;

}
