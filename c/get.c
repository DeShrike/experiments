#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

char hostname[30] = "sde-nb-222";
int port = 80;    
char serviceMethod[] = "/api/button1";
// char hostIP[30] = "x.x.x.x";

char getRequest[1000] = {0};
// char request[1000];
char response[1000];
struct hostent *server;
struct sockaddr_in serveraddr;

void pushData ()
{
    sprintf(getRequest, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", serviceMethod, hostname);

    server = gethostbyname(hostname);
    //strcpy (server, "52.15.222.145"); 
    if (server == NULL)
    {
        printf("gethostbyname() failed\n");
        return;
    }
    else
    {
        // printf("\nserver - %s", server->h_addr_list[0]);
        printf("IP = ");
        unsigned int j = 0;
        while (server -> h_addr_list[j] != NULL)
        {
            printf("%d: %s ", j, inet_ntoa(*(struct in_addr*)(server -> h_addr_list[j])));
            j++;
        }
    }
     
    printf("\n\n");
 
    int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
     
    if (tcpSocket < 0)
    {
        printf("Error opening socket\n");
        return;
    }

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
 
    bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
     
    serveraddr.sin_port = htons(port);
     
    if (connect(tcpSocket, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Error Connecting\n");
        close(tcpSocket);
        return;
    }
   
    printf("-----REQUEST----\n");

    printf("\n%s", getRequest);
     
    if (send(tcpSocket, getRequest, strlen(getRequest), 0) < 0)
    {
        fprintf(stderr, "Error with send()");
        close(tcpSocket);
        return;
    }
             
    bzero(response, 1000);
     
    printf("-----RESPONSE----\n");
    
    recv(tcpSocket, response, 999, 0);
    
    printf("\n%s\n", response);
    
    printf("-----END-----\n");
     
    close(tcpSocket);
}

int main(int argc, char** argv) 
{
    pushData ();
    return (EXIT_SUCCESS);
}
