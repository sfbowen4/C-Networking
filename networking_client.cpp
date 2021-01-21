#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
    
    // create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr("10.101.11.68");

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // check for error with the connection
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket \n\n");
    }

    char server_response[1024];
    char end_message[] = "--end--";
    char response[] = "Thanks!";
    do {
    // receive data from the server
    recv(network_socket, &server_response, sizeof(server_response), 0);
    send(network_socket, response, sizeof(response), 0);

    // print out the server's response
    printf("The server sent the data: %s\n", server_response);
    printf("Enter a response: ");
    scanf("%s", response);
    } while (strcmp(server_response, end_message) != 0);

    // close the socket
    printf("Closing connection...\n");
    send(network_socket, end_message, sizeof(end_message), 0);
    close(network_socket);

    return 0;
}
    