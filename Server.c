#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "http_request.h"

// char* split_on_C(char *str){
    
// }

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

HttpRequest* parseHttpRequest(char *request){

    HttpRequest *http_request = http_request_create();

    char *our_request = request;
    //printf("%s", our_request);
    char *sep = "\n";
    char *string_message = strtok(our_request, sep);
    printf("%s", string_message);
    http_request->method = string_message;

    //printf("%s", http_request->method);

    // 1) Сплит по /n
    // 2) ОБработка превой строки (разделить по пробелам)
    // 3) Сплит по : 

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

    parseHttpRequest(request);


    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);    
    
    // close the socket
    close(server_socket);

    return 0;

}
