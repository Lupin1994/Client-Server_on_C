#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "reckon_request.h"


InputRequest* reckon_request_create(){
    InputRequest *reqest = (InputRequest*)malloc(syzeof(InputRequest));
    reqest->request = NULL;
    reqest->get = NULL;
    reqest->host = NULL;
    reqest->user_agent = NULL;
    reqest->accept = NULL;
}

InputRequest* parseInputRequest(char *request){

    printf("1");
    InputRequest *Our_reqest = reckon_request_create();
    Our_reqest->request = request;
    printf(Our_reqest->request);
    char sep = "\n";
    char *string_message = strtok(Our_reqest->request, sep);

    while (string_message != NULL)
    {
        printf("%s\n", string_message);
        string_message = strtok(NULL,sep);

        if (Our_reqest->get == NULL)
        {
            Our_reqest->get = string_message;
        }
        else if (Our_reqest->host == NULL)
        {
            Our_reqest->host = string_message;
        }
        else if (Our_reqest->user_agent == NULL)
        {
            Our_reqest->user_agent = string_message;
        }
        else
        {
            Our_reqest->accept = string_message;
        }
    }
    //return Our_reqest;
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
		puts("accept failed");
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

    parseInputRequest(request);


    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);    
    
    // close the socket
    close(server_socket);

    return 0;

}
